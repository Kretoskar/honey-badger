#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Systems/PhysicsSystem.h"

#include "HoneyBadgerCore/ECS/Public/Components/RigidbodyComponent.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

void HoneyBadger::PhysicsSystem::Register(ECS& ecs)
{
	REGISTER_SYSTEM()
	REGISTER_COMPONENT_IN_SYSTEM(TransformComponent)
	REGISTER_COMPONENT_IN_SYSTEM(RigidbodyComponent)
}

void HoneyBadger::PhysicsSystem::Update(float deltaTime)
{
	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		RigidbodyComponent& rbComp = _ecs->GetComponent<RigidbodyComponent>(entity);

		static Vec3 gravity = Vec3(0, -9.81f, 0);

		rbComp.Force += gravity * rbComp.Mass;
		rbComp.Velocity += rbComp.Force * (1.0f / rbComp.Mass) * deltaTime * 10000.0f;

		transformComp.Position += rbComp.Velocity * deltaTime;

		rbComp.Force = Vec3(0.0f, 0.0f, 0.0f);
	}
}

HoneyBadger::CollisionResult HoneyBadger::PhysicsSystem::SphereBoxCollision(const TransformComponent& boxTransform, const TransformComponent& sphereTransform, float sphereRadius)
{
	CollisionResult res;

	HoneyBadger::Mat4 boxInWorld = boxTransform.WorldMatrix;
	HoneyBadger::Mat4 boxInWorldInverse = boxInWorld.Inverse();
	HoneyBadger::Vec3 sphereCenterInBoxSpace = HoneyBadger::Mat4::TransformVector(boxInWorldInverse, sphereTransform.Position);
	//... AABB here
	res.wasCollision = true;
	return res;
}
