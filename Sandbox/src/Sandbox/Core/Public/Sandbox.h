#pragma once

#include "HoneyBadgerGame/Core/Public/Game.h"
#include "Sandbox/SandboxCamera.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace Sand
{
	class CarGame : public HoneyBadgerGame::Game
	{
	public:
		virtual bool Init_Internal() override;
		virtual void BeginPlay_Internal() override;
		virtual void Tick_Internal(float deltaTime) override;
		virtual void EndPlay_Internal() override;

		HoneyBadger::Entity camEntity;
		HoneyBadger::Entity camArmEntity;
		HoneyBadger::Entity carEntity;
		HoneyBadger::Entity frontLeftTireEntity;
		HoneyBadger::Entity backLeftTireEntity;

		HoneyBadger::Entity frontRightTireEntity;
		HoneyBadger::Entity backRightTireEntity;

		HoneyBadger::Vec3 tireToCar;

		HoneyBadger::Vec3 flTireToFRTire;
		HoneyBadger::Vec3 blTireToBRTire;

		float tireToTireLen = 0.0f;

		void HandleInput();

		bool forwardPressed = false;
		bool backwardPressed = false;
		bool rightPressed = false;
		bool leftPressed = false;

		void OnForwardPressed(void* payload);
		void OnForwardReleased(void* payload);

		void OnBackwardPressed(void* payload);
		void OnBackwardReleased(void* payload);

		void OnRightPressed(void* payload);
		void OnRightReleased(void* payload);

		void OnLeftPressed(void* payload);
		void OnLeftReleased(void* payload);
	};
}