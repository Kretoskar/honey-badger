#pragma once

#include "HoneyBadgerGame/Core/Public/Game.h"

namespace Sandbox
{
	class Sandbox : public HoneyBadgerGame::Game
	{
		virtual bool Init_Internal();
		virtual void BeginPlay_Internal();
		virtual void Tick_Internal();
		virtual void EndPlay_Internal();
	};
}