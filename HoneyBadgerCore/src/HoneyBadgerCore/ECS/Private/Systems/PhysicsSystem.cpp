#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Systems/PhysicsSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/BoxCollisionComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/RigidbodyComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/SphereColliderComponent.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"
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
				static float baseBounceRate = 50.0f;

				float dot = HoneyBadger::Vec3::Dot(rbComp.Velocity.Normalized(), res.hitSurfaceNormal);

				rbComp.Velocity -= 
					res.hitSurfaceNormal * dot * (1 + rbComp.Bounciness) * rbComp.Velocity.Len();
			}
		}

		static Vec3 gravity = Vec3(0, -9.81f, 0);

		rbComp.Force += gravity * rbComp.Mass * rbComp.Mass;
		rbComp.Velocity += rbComp.Force * (1.0f / rbComp.Mass) * deltaTime * 10000.0f;
		rbComp.Velocity += Vec3(0.0f, 0.0f, -1.0f) * deltaTime * 50000.0f;

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
	
	// TODO: inside and normal check in one pass

	// check if inside
	if (std::fabsf(sphereCenterInBoxSpace.x) - sphereRadius <= boxScale.x / 2 &&
		std::fabsf(sphereCenterInBoxSpace.y) - sphereRadius <= boxScale.y / 2 &&
		std::fabsf(sphereCenterInBoxSpace.z) - sphereRadius <= boxScale.z / 2)
	{
		res.wasCollision = true;
	}
	else
	{
		return res;
	}

	float distances[3];
	distances[0] = std::fabsf(sphereCenterInBoxSpace.x - boxScale.x / 2);
	distances[1] = std::fabsf(sphereCenterInBoxSpace.y - boxScale.y / 2);
	distances[2] = std::fabsf(sphereCenterInBoxSpace.z - boxScale.z / 2);

	float dist = distances[0];
	res.hitSurfaceNormal = (distances[0] > 0) - (distances[0] < 0) > 0 ? 
		boxInWorld.forward.ToVec3().Normalized() :
		boxInWorld.forward.ToVec3().Normalized() * -1.0f;

	if (distances[1] < dist)
	{
		dist = distances[1];
		res.hitSurfaceNormal = (distances[1] > 0) - (distances[1] < 0) > 0 ?
			boxInWorld.up.ToVec3().Normalized() :
			boxInWorld.up.ToVec3().Normalized() * -1.0f;
	}
	if (distances[2] < dist)
	{
		res.hitSurfaceNormal = (distances[2] > 0) - (distances[2] < 0) > 0 ?
			boxInWorld.right.ToVec3().Normalized() :
			boxInWorld.right.ToVec3().Normalized() * -1.0f;
	}

	res.hitSurfaceNormal.Normalize();
	res.penetrationDepth = dist;

	return res;
}