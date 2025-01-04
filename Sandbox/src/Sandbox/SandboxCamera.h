#pragma once

#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"
#include "HoneyBadgerGame/Core/Public/Game.h"

namespace Sand
{
	class SandboxCamera : public HoneyBadger::Camera
	{
	public:
		SandboxCamera(HoneyBadger::Window* inWindow, HoneyBadger::Vec3 position)
			: Camera(inWindow, position) {}

		void Init(std::shared_ptr<HoneyBadger::ECS> inEcs, HoneyBadgerGame::Game* inGame);
		virtual void Update();

		virtual void OnRightMouseButtonClick(void* event) {}
		virtual void OnRightMouseButtonRelease(void* event) {}

		virtual void OnForwardPressed(void* payload) {}
		virtual void OnForwardReleased(void* payload) {}

		virtual void OnBackwardPressed(void* payload) {}
		virtual void OnBackwardReleased(void* payload) {}

		virtual void OnRightPressed(void* payload) {}
		virtual void OnRightReleased(void* payload) {}

		virtual void OnLeftPressed(void* payload) {}
		virtual void OnLeftReleased(void* payload) {}

		virtual void OnMouseMoved(void* payload) {}

		std::shared_ptr<HoneyBadger::ECS> ecs;
		HoneyBadgerGame::Game* game;
	};
}