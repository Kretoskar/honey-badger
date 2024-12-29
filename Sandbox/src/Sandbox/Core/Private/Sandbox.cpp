#include "Sandbox/Core/Public/Sandbox.h"

bool Sandbox::Sandbox::Init_Internal()
{
	return true;
}

void Sandbox::Sandbox::BeginPlay_Internal()
{
}

void Sandbox::Sandbox::Tick_Internal()
{
// TODO: delta time
	HoneyBadger::Entity e = GetEntityByName("car");
	HoneyBadger::TransformComponent& tc = _ecs->GetComponent<HoneyBadger::TransformComponent>(e);
	tc.Rotation = tc.Rotation * HoneyBadger::Quat(0.1f, HoneyBadger::Vec3(0.0f, 1.0f, 0.0f));
}

void Sandbox::Sandbox::EndPlay_Internal()
{
}
