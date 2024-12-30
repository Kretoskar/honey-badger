#pragma once

#include <GLFW/glfw3.h>

namespace HoneyBadger
{
	class UserInterface
	{
	public:
		bool Init(GLFWwindow* window);
		void CreateFrame(double deltaTime);
		void Render();
		void Cleanup();

	protected:
		virtual void CreateWidgets() = 0;

		double dt = 0.0;
	};
}