#pragma once

#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

// TODO: fix ECS || signatures to join this and RenderingSystem

namespace HoneyBadger
{
	class Camera;

	class ModelRenderingSystem : public System
	{
	public:
		void Register(ECS& ecs, Camera* camera);
		void Render();

	private:
		Camera* _camera;
	};
}