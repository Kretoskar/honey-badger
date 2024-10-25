#pragma once
#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadgerEditor
{
	class HoneyBadgerEditor
	{
	public:
		bool Init(uint32_t width, uint32_t height, HoneyBadger::HBString name);
		void Start();
		void ShutDown();

	private:
		void ShutDown_Internal();

		bool _shouldClose = false;

		HoneyBadger::Engine _engine;
		HoneyBadger::Window _window;
	};
}