#pragma once

#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	class Camera;

	class ColliderRenderingSystem : public System
	{
	public:
		void Register(ECS& ecs, Camera* camera);
		void Render();

	private:
		Camera* _camera;
	};
}