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
	HoneyBadger::Entity car = game->GetEntityByName("car");

	HoneyBadger::TransformComponent& camTransform = ecs->GetComponent<HoneyBadger::TransformComponent>(game->GetEntityByName("cam"));
	HoneyBadger::TransformComponent& camArmTransform = ecs->GetComponent<HoneyBadger::TransformComponent>(game->GetEntityByName("camArm"));
	HoneyBadger::TransformComponent& carTransform = ecs->GetComponent<HoneyBadger::TransformComponent>(game->GetEntityByName("car"));

	_position = { camTransform.WorldMatrix.position.x, camTransform.WorldMatrix.position.y, camTransform.WorldMatrix.position.z };
	_orientation = { camArmTransform.WorldMatrix.position.x, camArmTransform.WorldMatrix.position.y, camArmTransform.WorldMatrix.position.z};
	// look to the front of the car
	_orientation += HoneyBadger::Vec3(carTransform.ToMat4().forward.x, carTransform.ToMat4().forward.y, carTransform.ToMat4().forward.z) * -100.0f;

	_view = HoneyBadger::Mat4::LookAt(_position, _orientation, _up);
	
	_projection = HoneyBadger::Mat4::Perspective(_FOVdeg, static_cast<float>(_width) / static_cast<float>(_height), _nearPlane, _farPlane);
}