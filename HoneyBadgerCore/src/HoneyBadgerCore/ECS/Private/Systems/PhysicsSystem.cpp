#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Systems/PhysicsSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/BoxCollisionComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/RigidbodyComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/SphereColliderComponent.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

void HoneyBadger::PhysicsSystem::Register(ECS& ecs)
{
	REGISTER_SYSTEM()
	REGISTER_COMPONENT_IN_SYSTEM(TransformComponent)
	REGISTER_COMPONENT_IN_SYSTEM(RigidbodyComponent)
	REGISTER_COMPONENT_IN_SYSTEM(SphereColliderComponent)

	
}

void HoneyBadger::PhysicsSystem::Update(float deltaTime)
{
	boxes.clear();
	// shitty hack to cache all box collisions on register, as they're static
	for (Entity e : _ecs->LivingEntities)
	{
		if (BoxCollisionComponent* boxColl = _ecs->GetComponentPtr<BoxCollisionComponent>(e))
		{
			if (TransformComponent* boxTransf = _ecs->GetComponentPtr<TransformComponent>(e))
			{
				boxes.push_back(boxTransf);
			}
		}
	}

	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		RigidbodyComponent& rbComp = _ecs->GetComponent<RigidbodyComponent>(entity);
		SphereColliderComponent& sphereCollComp = _ecs->GetComponent<SphereColliderComponent>(entity);

		// TODO: hold coll in octree
		for (TransformComponent* box : boxes)
		{
			CollisionResult res = SphereBoxCollision(*box, transformComp, sphereCollComp.Radius);
			if (res.wasCollision)
			{
				return;
			}
		}

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

	// get sphere location in box's space, so that box is AABB
	HoneyBadger::Mat4 boxInWorld = boxTransform.WorldMatrix;
	HoneyBadger::Mat4 boxInWorldInverse = boxInWorld.Inverse();
	HoneyBadger::Mat4 sphereInBoxSpace = boxInWorldInverse * sphereTransform.WorldMatrix;
	HoneyBadger::Vec3 sphereCenterInBoxSpace = sphereInBoxSpace.position.ToVec3();
	
	// now it's just AABB sphere intersection
	HoneyBadger::Vec3 boxPosition = boxInWorld.position.ToVec3();
	HoneyBadger::Vec3 boxScale = boxInWorld.GetScale();
	HoneyBadger::Vec3 c1 = Vec3(
		boxPosition.x + boxScale.x / 2, 
		boxPosition.y + boxScale.y / 2,
		boxPosition.z + boxScale.z / 2);

	HoneyBadger::Vec3 c2 = Vec3(
		boxPosition.x - boxScale.x / 2,
		boxPosition.y - boxScale.y / 2,
		boxPosition.z - boxScale.z / 2);
	
	float distSquared = sphereRadius * sphereRadius;
	
	if (sphereCenterInBoxSpace.x < c1.x) 
	{
		distSquared -= (sphereCenterInBoxSpace.x - c1.x) * (sphereCenterInBoxSpace.x - c1.x);
	}
	else if (sphereCenterInBoxSpace.x > c2.x) 
	{
		distSquared -= (sphereCenterInBoxSpace.x - c2.x) * (sphereCenterInBoxSpace.x - c2.x);
	}
	if (sphereCenterInBoxSpace.x < c1.x)
	{
		distSquared -= (sphereCenterInBoxSpace.y - c1.y) * (sphereCenterInBoxSpace.y - c1.y);
	}
	else if (sphereCenterInBoxSpace.y > c2.y) 
	{
		distSquared -= (sphereCenterInBoxSpace.y - c2.y) * (sphereCenterInBoxSpace.y - c2.y);
	}
	if (sphereCenterInBoxSpace.z < c1.z) 
	{
		distSquared -= (sphereCenterInBoxSpace.z - c1.z) * (sphereCenterInBoxSpace.z - c1.z);
	}
	else if (sphereCenterInBoxSpace.z > c2.z) 
	{
		distSquared -= (sphereCenterInBoxSpace.z - c2.z) * (sphereCenterInBoxSpace.z - c2.z);
	}

	res.wasCollision = distSquared > 0;

	return res;
}