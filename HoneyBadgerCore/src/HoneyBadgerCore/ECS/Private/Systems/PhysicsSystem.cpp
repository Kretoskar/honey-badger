#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Systems/PhysicsSystem.h"

#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/RigidbodyComponent.h"

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