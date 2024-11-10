#include "hbpch.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

bool HoneyBadger::Window::Init(HBString name, bool fullscreen)
{
	if (!glfwInit())
	{
		HB_LOG_ERROR("Failed to initialize window")
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	_width = mode->width;
	_height = mode->height;
	_name = name;

	_glfwWindow = glfwCreateWindow(
		_width,
		_height,
		_name.Get(),
		fullscreen ? glfwGetPrimaryMonitor() : nullptr,
		nullptr);

	if (!_glfwWindow)
	{
		HB_LOG_ERROR("Failed to initialize window")
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_glfwWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
			HB_LOG_ERROR("Failed to initialize GLAD")
			return false;
	}

	glViewport(0, 0, _width, _height);
	glClearColor(0.09f, 0.09f, 0.15f, 1.00f);

	// force VSYNC
	glfwSwapInterval(1);

	BindWindowEvents();

	return true;
}

void HoneyBadger::Window::Update()
{
	glfwSwapBuffers(_glfwWindow);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HoneyBadger::Window::Shutdown()
{
	glfwDestroyWindow(_glfwWindow);
	glfwTerminate();
}
