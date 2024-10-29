#pragma once

#include <GLFW/glfw3.h>

namespace HoneyBadger
{
	class UserInterface
	{
	public:
		bool Init(GLFWwindow* window);
		void CreateFrame();
		void Render();
		void Cleanup();

	protected:
		virtual void CreateWidgets() = 0;
	};
}