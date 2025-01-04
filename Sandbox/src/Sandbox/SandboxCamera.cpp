#include "Sandbox/SandboxCamera.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"

void Sand::SandboxCamera::Init(std::shared_ptr<HoneyBadger::ECS> inEcs, HoneyBadgerGame::Game* inGame)
{
	game = inGame;
	ecs = inEcs;
}

void Sand::SandboxCamera::Update()
{
	HoneyBadger::Entity camE = game->GetEntityByName("cam");
	HoneyBadger::Entity camArmE = game->GetEntityByName("camArm");

	HoneyBadger::TransformComponent& camTransform = ecs->GetComponent<HoneyBadger::TransformComponent>(game->GetEntityByName("cam"));
	HoneyBadger::TransformComponent& camArmTransform = ecs->GetComponent<HoneyBadger::TransformComponent>(game->GetEntityByName("camArm"));

	_position = { camTransform.WorldMatrix.position.x, camTransform.WorldMatrix.position.y, camTransform.WorldMatrix.position.z };
	_orientation = { camArmTransform.WorldMatrix.position.x, camArmTransform.WorldMatrix.position.y, camArmTransform.WorldMatrix.position.z};

	_view = HoneyBadger::Mat4::LookAt(_position, _orientation, _up);
	_projection = HoneyBadger::Mat4::Perspective(_FOVdeg, static_cast<float>(_width) / static_cast<float>(_height), _nearPlane, _farPlane);
}