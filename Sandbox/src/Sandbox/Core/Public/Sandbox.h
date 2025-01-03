#pragma once

#include "HoneyBadgerGame/Core/Public/Game.h"

namespace Sandbox
{
	class Sandbox : public HoneyBadgerGame::Game
	{
		virtual bool Init_Internal() override;
		virtual void BeginPlay_Internal() override;
		virtual void Tick_Internal(float deltaTime) override;
		virtual void EndPlay_Internal() override;
	};
}