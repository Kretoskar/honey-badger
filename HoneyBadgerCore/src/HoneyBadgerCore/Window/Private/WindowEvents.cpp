#include "hbpch.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"


void HoneyBadger::Window::BindWindowEvents()
{
	{
		/* Save the pointer to the instance as user pointer */
		glfwSetWindowUserPointer(GetGlfwWindow(), this);

		/* Use a lambda to get the pointer and call the member function */
		glfwSetWindowPosCallback(GetGlfwWindow(), [](GLFWwindow* win, int xpos, int ypos)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleWindowMoveEvents(xpos, ypos);
		});

		glfwSetWindowIconifyCallback(GetGlfwWindow(), [](GLFWwindow* win, int minimized)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleWindowMinimizedEvents(minimized);
		});

		glfwSetWindowMaximizeCallback(GetGlfwWindow(), [](GLFWwindow* win, int maximized)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleWindowMaximizedEvents(maximized);
		});

		glfwSetWindowCloseCallback(GetGlfwWindow(), [](GLFWwindow* win)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleWindowCloseEvents();
		});

		glfwSetKeyCallback(GetGlfwWindow(), [](GLFWwindow* win, int key, int scancode, int action, int mods)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleKeyEvents(key, scancode, action, mods);
		});

		glfwSetMouseButtonCallback(GetGlfwWindow(), [](GLFWwindow* win, int button, int action, int mods)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleMouseButtonEvents(button, action, mods);
		});

		glfwSetCursorPosCallback(GetGlfwWindow(), [](GLFWwindow* win, double xpos, double ypos)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleMousePositionEvents(xpos, ypos);
		});

		glfwSetCursorEnterCallback(GetGlfwWindow(), [](GLFWwindow* win, int enter)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleMouseEnterLeaveEvents(enter);
		});

		glfwSetFramebufferSizeCallback(_glfwWindow, [](GLFWwindow* win, int width, int height)
		{
			Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));
			thisWindow->HandleWindowResizeEvents(win, width, height);
		});
	}
}

void HoneyBadger::Window::HandleWindowMoveEvents(int xpos, int ypos)
{
	HB_LOG_MESSAGE("Window moved: x: %i y: %i", xpos, ypos)
}

void HoneyBadger::Window::HandleWindowMinimizedEvents(int minimized)
{
	if (minimized)
	{
		HB_LOG_MESSAGE("Window has been minimized")
	}
	else
	{
		HB_LOG_MESSAGE("Window has been restored")
	}
}

void HoneyBadger::Window::HandleWindowMaximizedEvents(int maximized)
{
	if (maximized)
	{
		HB_LOG_MESSAGE("Window has been maximized")
	}
	else
	{
		HB_LOG_MESSAGE("Window has been restored")
	}
}

void HoneyBadger::Window::HandleWindowCloseEvents()
{
	HB_LOG_MESSAGE("Window has been closed")
}

void HoneyBadger::Window::HandleWindowResizeEvents(GLFWwindow* window, int width, int height)
{
	_width = width;
	_height = height;
	UpdateViewportSize();
}

void HoneyBadger::Window::HandleKeyEvents(int key, int scancode, int action, int mods)
{
	std::string actionName;

	switch (action)
	{
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	case GLFW_REPEAT:
		actionName = "repeated";
		break;
	default:
		actionName = "invalid";
		break;
	}

	HB_POST_EVENT(KeyboardEvent::Type(key, action, mods), nullptr)

	const char* keyName = glfwGetKeyName(key, 0);
	HB_LOG_MESSAGE("key %s (key %i, scancode %i) %s", keyName, key, scancode, actionName.c_str())
}

void HoneyBadger::Window::HandleMouseButtonEvents(int button, int action, int mods)
{
	std::string actionName;

	switch (action)
	{
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	case GLFW_REPEAT:
		actionName = "repeated";
		break;
	default:
		actionName = "invalid";
		break;
	}

	std::string mouseButtonName;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseButtonName = "left";
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mouseButtonName = "middle";
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseButtonName = "right";
		break;
	default:
		mouseButtonName = "other";
		break;
	}

	HB_POST_EVENT(MouseButtonEvent::Type(button, action, mods), nullptr)
	HB_LOG_MESSAGE("%s mouse button (%i) %s with mod %i", mouseButtonName.c_str(), button, actionName.c_str(), mods)
}

void HoneyBadger::Window::HandleMousePositionEvents(double xpos, double ypos)
{
	MousePositionEvent::MousePositionEventPayload payload = { static_cast<int>(xpos), static_cast<int>(ypos) };
	HB_POST_EVENT(MousePositionEvent::Type(), &payload)
}

void HoneyBadger::Window::HandleMouseEnterLeaveEvents(int enter)
{
	if (enter)
	{
		HB_LOG_MESSAGE("Mouse entered window")
	}
	else
	{
		HB_LOG_MESSAGE("Mouse left window")
	}
}

