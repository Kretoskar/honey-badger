#pragma once

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadgerGame
{
	class Game
	{
	public:
	
		bool Init(HoneyBadger::HBString name);
		void Start();
		void ShutDown();

	protected:
		virtual bool Init_Internal() = 0;
		virtual void BeginPlay_Internal() = 0;
		virtual void Tick_Internal() = 0;
		virtual void EndPlay_Internal() = 0;

	private:
		void BeginPlay();
		void Tick();
		void EndPlay();

		bool _shouldClose = false;

		HoneyBadger::Engine _engine;
		HoneyBadger::Window _window;
	};
}