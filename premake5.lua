workspace "HoneyBadger"
	language "C++"
	architecture "x86_64"
	startproject "HoneyBadgerEditor"
	configurations { "Debug", "Release" }

	filter { "configurations:Debug" }
		symbols "On"

	filter { "configurations:Release" }
		optimize "On"

	-- Reset the filter for other settings
	filter { }

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

function includeGLFW()
	includedirs "Libraries/GLFW/Include"
end

function linkGLFW()
	libdirs "Libraries/GLFW/lib-vc2022"

	-- static lib should not link against GLFW
	filter "kind:not StaticLib"
		links "glfw3"
	filter {}
end

project "Glad"
    kind "StaticLib"
	location "Libraries/GLAD"
    language "C"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Libraries/GLAD/include/glad/glad.h",
        "Libraries/GLAD/include/KHR/khrplatform.h",
        "Libraries/GLAD/src/glad.c"
    }

    includedirs
    {
        "Libraries/GLAD/include"
    }
    
    filter "system:windows"
        systemversion "latest"

		filter {}

project "HoneyBadgerCore"
	location "HoneyBadgerCore"
	kind "StaticLib"

	pchheader "hbpch.h"
    pchsource "HoneyBadgerCore/src/hbpch.cpp"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

	includedirs
	{
		"HoneyBadgerCore/src",
		"Libraries/GLAD/include"
	}

	links
	{
		"Glad"
	}

	includeGLFW()

	filter {}

    function useHoneyBadgerCore()
        includedirs "HoneyBadgerCore/src"
        links "HoneyBadgerCore"
		includeGLFW()
        linkGLFW()
    end

project "HoneyBadgerEditor"
	location "HoneyBadgerEditor"
    kind "ConsoleApp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

	includedirs
	{
		"HoneyBadgerEditor/src",
		"Libraries/GLAD/include"
	}

    useHoneyBadgerCore()

	filter { "system:windows" }
    	links { "OpenGL32" }
	filter {}

project "HoneyBadgerGame"
	location "HoneyBadgerGame"
    kind "StaticLib"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

	includedirs
	{
		"HoneyBadgerGame/src",
		"Libraries/GLAD/include"
	}

    useHoneyBadgerCore()

	function useHoneyBadgerGame()
		useHoneyBadgerCore()
        includedirs "HoneyBadgerGame/src"
        links "HoneyBadgerGame"
    end

	filter { "system:windows" }
   		links { "OpenGL32" }
	filter {}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Sandbox/src",
		"Libraries/GLAD/include"
	}

	useHoneyBadgerGame()

	filter { "system:windows" }
		links { "OpenGL32" }
	filter {}