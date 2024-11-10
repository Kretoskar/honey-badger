#include "hbpch.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"

bool HoneyBadger::Window::Init(WindowInitSettings InitSettings)
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

	_width = InitSettings.Width;
	_height = InitSettings.Height;
	_name = InitSettings.Name;
	_state = InitSettings.StartingState;
	_viewportMarginRatioLeft = InitSettings.ViewportMarginRatioLeft;
	_viewportMarginRatioRight = InitSettings.ViewportMarginRatioRight;
	_viewportMarginRatioTop = InitSettings.ViewportMarginRatioTop;
	_viewportMarginRatioBottom = InitSettings.ViewportMarginRatioBottom;

	_glfwWindow = glfwCreateWindow(
		_width,
		_height,
		_name.Get(),
		_state == WindowState::Fullscreen ? glfwGetPrimaryMonitor() : nullptr,
		nullptr);

	if (_state == WindowState::Maximized)
	{
		glfwMaximizeWindow(GetGlfwWindow());
		_width = mode->width;
		_height = mode->height;
	}

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

	UpdateViewportSize();
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

void HoneyBadger::Window::UpdateViewportSize()
{
	glViewport
	(
		_width * _viewportMarginRatioLeft,
		_height * _viewportMarginRatioBottom,
		_width - (_width * _viewportMarginRatioLeft) - (_width * _viewportMarginRatioRight),
		_height - (_height * _viewportMarginRatioTop) - (_height * _viewportMarginRatioBottom)
	);
}