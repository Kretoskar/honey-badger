#pragma once

#include <GLFW/glfw3.h>
#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadger
{
	class Window
	{
	public:
		bool Init();
		void Update();
		void Shutdown();

		GLFWwindow* GetGlfwWindow() const { return _glfwWindow; }
		bool GetShouldClose() const { return _glfwWindow ? glfwWindowShouldClose(_glfwWindow) : false; }

	private:
		GLFWwindow* _glfwWindow = nullptr;
		bool _isValid = false;

		uint32_t _width, _height;
		HBString _name;
	};
}