#pragma once

#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"

namespace HoneyBadger
{
	struct CollisionResult
	{
		bool wasCollision = false;
		float penetrationDepth = 0.0f;
		HoneyBadger::Vec3 hitSurfaceNormal {};
		HoneyBadger::Vec3 hitLocation {};
	};

	class PhysicsSystem : public System
	{
	public:
		void Register(ECS& ecs);
		void Update(float deltaTime);

		CollisionResult SphereBoxCollision(const TransformComponent& boxTransform, const TransformComponent& sphereTransform, float sphereRadius);
		CollisionResult Raycast(const HoneyBadger::Vec3& start, const HoneyBadger::Vec3& end);

		std::vector<TransformComponent*> boxes;
	};
}