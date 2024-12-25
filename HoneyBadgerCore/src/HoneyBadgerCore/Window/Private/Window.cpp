#include "hbpch.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"

float rectangleVertices[] =
{
	// Coords    // texCoords
	 2.0f, -2.0f,  1.0f, 0.0f,
	-2.0f, -2.0f,  0.0f, 0.0f,
	-2.0f,  2.0f,  0.0f, 1.0f,
	 2.0f,  2.0f,  1.0f, 1.0f,
	 2.0f, -2.0f,  1.0f, 0.0f,
	-2.0f,  2.0f,  0.0f, 1.0f
};

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

	glEnable(GL_DEPTH_TEST);

	// Prepare framebuffer rectangle VBO and VAO
	unsigned int rectVBO;
	glGenVertexArrays(1, &_rectVao);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(_rectVao);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	glGenTextures(1, &_framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, _framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _framebufferTexture, 0);

	glGenRenderbuffers(1, &_renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width , _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.00f);


	// force VSYNC
	glfwSwapInterval(1);

	BindWindowEvents();

	if (_state == WindowState::Maximized)
	{
		glfwMaximizeWindow(GetGlfwWindow());
	}



	return true;
}

void HoneyBadger::Window::Update()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	HoneyBadger::AssetsRegistry::Instance->GetShaderByName("framebuffer")->SetUniform1f("screenTexture", 0);
	HoneyBadger::AssetsRegistry::Instance->GetShaderByName("framebuffer")->SetUniform1f("width", _finalWidth);
	HoneyBadger::AssetsRegistry::Instance->GetShaderByName("framebuffer")->SetUniform1f("height", _finalHeight);
	glDisable(GL_DEPTH_TEST);
	HoneyBadger::AssetsRegistry::Instance->GetShaderByName("framebuffer")->Bind();
	glBindVertexArray(_rectVao);
	glBindTexture(GL_TEXTURE_2D, _framebufferTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

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
	_finalWidth = _width - (_width * _viewportMarginRatioLeft) - (_width * _viewportMarginRatioRight);
	_finalHeight = _height - (_height * _viewportMarginRatioTop) - (_height * _viewportMarginRatioBottom);
	glViewport
	(
		_width * _viewportMarginRatioLeft,
		_height * _viewportMarginRatioBottom,
		_finalWidth,
		_finalHeight
	);
}