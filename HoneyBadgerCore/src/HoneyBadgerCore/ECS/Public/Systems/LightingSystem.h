#pragma once

#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	class Camera;

	class LightRenderingSystem : public System
	{
	public:
		void Register(ECS& ecs, Camera* camera);
		void UpdateShaders();

	private:
		Camera* _camera;
	};
}