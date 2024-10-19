#include "hbpch.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

bool HoneyBadger::Window::Init(uint32_t width, uint32_t height, HBString name)
{
	if (!glfwInit())
	{
		HB_LOG_ERROR("Failed to initialize window")
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_width = width;
	_height = height;
	_name = name;

	_glfwWindow = glfwCreateWindow(
		_width,
		_height,
		_name.Get(),
		nullptr,
		nullptr);

	if (!_glfwWindow)
	{
		HB_LOG_ERROR("Failed to initialize window")
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_glfwWindow);

	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	//{
	//	TURTLE_LOG_ERROR("Failed to initialize GLAD")
	//		return false;
	//}

	glViewport(0, 0, _width, _height);
	glClearColor(0.15f, 0.5f, 1.0f, 1.0f);

	// force VSYNC
	glfwSwapInterval(1);

	//BindWindowEvents();

	return true;
}

void HoneyBadger::Window::Update()
{
	glfwSwapBuffers(_glfwWindow);
	glfwPollEvents();
}

void HoneyBadger::Window::Shutdown()
{
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}
