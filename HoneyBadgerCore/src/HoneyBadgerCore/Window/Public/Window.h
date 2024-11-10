#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadger
{
	class Window
	{
	public:
		bool Init(HBString name, bool fullscreen);
		void Update();
		void Shutdown();

		GLFWwindow* GetGlfwWindow() const { return _glfwWindow; }
		bool GetShouldClose() const { return _glfwWindow ? glfwWindowShouldClose(_glfwWindow) : false; }

	private:
		void BindWindowEvents();

		void HandleWindowMoveEvents(int xpos, int ypos);
		void HandleWindowMinimizedEvents(int minimized);
		void HandleWindowMaximizedEvents(int maximized);
		void HandleWindowCloseEvents();
		void HandleWindowResizeEvents(GLFWwindow* window, int width, int height);

		void HandleKeyEvents(int key, int scancode, int action, int mods);
		void HandleMouseButtonEvents(int button, int action, int mods);
		void HandleMousePositionEvents(double xpos, double ypos);
		void HandleMouseEnterLeaveEvents(int enter);

		GLFWwindow* _glfwWindow = nullptr;

		uint32_t _width, _height;
		HBString _name;
	};
}