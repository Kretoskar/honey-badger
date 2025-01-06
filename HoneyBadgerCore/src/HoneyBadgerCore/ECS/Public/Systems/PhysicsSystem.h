#pragma once

#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"

namespace HoneyBadger
{
	struct CollisionResult
	{
		bool wasCollision = false;
	};

	class PhysicsSystem : public System
	{
	public:
		void Register(ECS& ecs);
		void Update(float deltaTime);

		CollisionResult SphereBoxCollision(const TransformComponent& boxTransform, const TransformComponent& sphereTransform, float sphereRadius);
	};
}