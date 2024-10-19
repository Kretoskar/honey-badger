#include "hbpch.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

bool HoneyBadger::Window::Init()
{
	if (!glfwInit())
	{
		//HB_LOG_ERROR("Failed to initialize window")
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_width = 1920;// HoneyBadger::Engine::EngineSettings->GetWindowSettings().Width;
	_height = 1080;// HoneyBadger::Engine::EngineSettings->GetWindowSettings().Height;
	_name = "x";// HoneyBadger::Engine::EngineSettings->GetWindowSettings().Name;

	_glfwWindow = glfwCreateWindow(
		_width,
		_height,
		_name.Get(),
		nullptr,
		nullptr);

	if (!_glfwWindow)
	{
		//TURTLE_LOG_ERROR("Failed to initialize window")
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
