#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Systems/PhysicsSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/BoxCollisionComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/RigidbodyComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/SphereColliderComponent.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

using namespace HoneyBadger;

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

		static Vec3 gravity = Vec3(0, -0.981f, 0);
		rbComp.Force += gravity * rbComp.Mass * rbComp.Mass * deltaTime;

		for (const Vec3& force : rbComp.Forces)
		{
			rbComp.Force += force * deltaTime;
		}
		rbComp.Forces.clear();

		rbComp.Velocity += rbComp.Force * (1.0f / rbComp.Mass);

		// TODO: hold coll in octree
		for (TransformComponent* box : boxes)
		{
			CollisionResult res = SphereBoxCollision(*box, transformComp, sphereCollComp.Radius);
			if (res.wasCollision)
			{
				float dot = HoneyBadger::Vec3::Dot(rbComp.Velocity, res.hitSurfaceNormal);

				rbComp.Velocity +=
					res.hitSurfaceNormal * std::fabsf(dot);// * (1.0f + rbComp.Bounciness);// /** (1.0f  + rbComp.Bounciness)*/ * rbComp.Velocity.Len();
			}
		}

		transformComp.Position += rbComp.Velocity;
		// friction hack
		rbComp.Velocity = Vec3(rbComp.Velocity.x * 0.999f, rbComp.Velocity.y, rbComp.Velocity.z * 0.999f);
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

CollisionResult HoneyBadger::PhysicsSystem::Raycast(const HoneyBadger::Vec3& start, const HoneyBadger::Vec3& end)
{
	CollisionResult res;
	float closestHit = std::numeric_limits<float>::infinity();

	// TODO: cover cases where raycast goes through the whole collider
	for (TransformComponent* box : boxes)
	{
		Mat4 boxInWorld = box->WorldMatrix;
		Mat4 boxInWorldInverse = boxInWorld.Inverse();

		Mat4 startMat = Mat4::FromPosition(start);
		Mat4 startBoxSpace = boxInWorldInverse * startMat;
		Vec3 startPosInBoxSpace = startBoxSpace.position.ToVec3();

		Mat4 endMat = Mat4::FromPosition(end);
		Mat4 endBoxSpace = boxInWorldInverse * endMat;
		Vec3 endPosInBoxSpace = endBoxSpace.position.ToVec3();

		//HB_LOG_ERROR("hit %f %f %f", endPosInBoxSpace.x, endPosInBoxSpace.y, endPosInBoxSpace.z)

		Vec3 boxScale = boxInWorld.GetScale();

		// check if end is inside
		if (!(std::fabsf(endPosInBoxSpace.x) <= 0.5f &&
			std::fabsf(endPosInBoxSpace.y) <= 0.5f &&
			std::fabsf(endPosInBoxSpace.z) <= 0.5f))
		{
			continue;
		}

		Vec3 boxMin = boxScale * (1.0f / 2.0f);
		Vec3 boxMax = boxScale * (1.0f / 2.0f);

		Vec3 rayDirInBoxSpace = endPosInBoxSpace - startPosInBoxSpace;

		float tMin = -std::numeric_limits<float>::infinity();
		float tMax = std::numeric_limits<float>::infinity();

		int hitAxis = -1;

		for (int i = 0; i < 3; ++i) 
		{
			// Access coordinates via pointer arithmetic
			float rayOriginComp = (&startPosInBoxSpace.x)[i];
			float rayDirectionComp = (&rayDirInBoxSpace.x)[i];
			float boxMinComp = (&boxMin.x)[i];
			float boxMaxComp = (&boxMax.x)[i];

			if (std::abs(rayDirectionComp) < 1e-8) 
			{ // Ray is parallel to this slab
				if (rayOriginComp < boxMinComp || rayOriginComp > boxMaxComp) 
				{
					continue;
				}
			}
			else 
			{
				// Compute intersection points with the slabs
				float t1 = (boxMinComp - rayOriginComp) / rayDirectionComp;
				float t2 = (boxMaxComp - rayOriginComp) / rayDirectionComp;

				if (t1 > t2)
				{ 
					std::swap(t1, t2);
				}

				tMin = std::max(tMin, t1);
				tMax = std::min(tMax, t2);

				if (tMin > tMax) 
				{
					continue;
				}
				else
				{
					hitAxis = i;
				}

			}
		}

		if (tMin < 0) 
		{
			continue;
		}

		Vec3 rayInWorldSpace = end - start;
		Vec3 hitLoc = start + (rayInWorldSpace * tMin);
		// Compute intersection point
		float newDist = Vec3::Distance(start, hitLoc);
		if (newDist < closestHit)
		{
			closestHit = newDist;
			res.hitLocation = hitLoc;
			res.wasCollision = true;

			res.hitSurfaceNormal = { 0.0f, 0.0f, 0.0f };
			if (hitAxis >= 0) 
			{
				(&res.hitSurfaceNormal.x)[hitAxis] = rayDirInBoxSpace.v[hitAxis] > 0 ? -1.0f : 1.0f;
			}
		}

		Mat4 normalMat = Mat4::FromPosition(res.hitSurfaceNormal);
		Mat4 normalWorldSpace = box->WorldRotMatrix * normalMat;
		res.hitSurfaceNormal = normalWorldSpace.position.ToVec3();
	}

	return res;
}