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

project "HoneyBadgerCore"
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
		"HoneyBadgerCore/src"
	}

	includeGLFW()

    function useHoneyBadgerCore()
        includedirs "HoneyBadgerCore/src"
        links "HoneyBadgerCore"
		includeGLFW()
        linkGLFW()
    end

project "HoneyBadgerEditor"
    kind "ConsoleApp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    useHoneyBadgerCore()

filter { "system:windows" }
    links { "OpenGL32" }

filter { "system:not windows" }
    links { "GL" }