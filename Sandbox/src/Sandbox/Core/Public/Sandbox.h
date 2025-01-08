#pragma once

#include "HoneyBadgerGame/Core/Public/Game.h"
#include "Sandbox/SandboxCamera.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace Sand
{
	class CarGame : public HoneyBadgerGame::Game
	{
		virtual bool Init_Internal() override;
		virtual void BeginPlay_Internal() override;
		virtual void Tick_Internal(float deltaTime) override;
		virtual void EndPlay_Internal() override;

		HoneyBadger::Entity camEntity;
		HoneyBadger::Entity camArmEntity;
		HoneyBadger::Entity carEntity;
		HoneyBadger::Entity frontLeftTireEntity;
		HoneyBadger::Entity backLeftTireEntity;
		HoneyBadger::Vec3 tireToCar;

		float tireToTireLen = 0.0f;
	};
}