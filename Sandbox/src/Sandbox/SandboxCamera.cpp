#include "Sandbox/SandboxCamera.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include <HoneyBadgerCore/Math/Public/MathCore.h>
#include "HoneyBadgerCore/Core/Public/EventSystem.h"

void Sand::SandboxCamera::Init(std::shared_ptr<HoneyBadger::ECS> inEcs, HoneyBadgerGame::Game* inGame)
{
	game = inGame;
	ecs = inEcs;

	HB_BIND_EVENT(HoneyBadger::MousePositionEvent::Type(), OnMouseMoved)
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
	_orientation += HoneyBadger::Vec3(carTransform.ToMat4().forward.x, carTransform.ToMat4().forward.y, carTransform.ToMat4().forward.z) * -200.0f;


	_view = HoneyBadger::Mat4::LookAt(_position, _orientation, _up);
	
	_projection = HoneyBadger::Mat4::Perspective(_FOVdeg, static_cast<float>(_width) / static_cast<float>(_height), _nearPlane, _farPlane);
}

void Sand::SandboxCamera::OnMouseMoved(void* payload)
{
	const int32_t posX = *static_cast<int32_t*>(payload);
	const int32_t posY = *reinterpret_cast<int32_t*>(static_cast<char*>(payload) + sizeof(int32_t));

	const float rotX = _sensitivity * static_cast<float>(posY - (_height / 2)) / _height / 1000.0f;
	const float rotY = _sensitivity * static_cast<float>(posX - (_width / 2)) / _width / 1000.0f;

	HoneyBadger::Entity camArmE = game->GetEntityByName("camArm");
	HoneyBadger::TransformComponent& camArmTransform = ecs->GetComponent<HoneyBadger::TransformComponent>(game->GetEntityByName("camArm"));
	camArmTransform.Rotation = camArmTransform.Rotation  * HoneyBadger::Quat(rotX, camArmTransform.ToMat4().right.ToVec3());
	camArmTransform.Rotation = camArmTransform.Rotation  * HoneyBadger::Quat(rotY, camArmTransform.ToMat4().up.ToVec3());

	glfwSetCursorPos(_window->GetGlfwWindow(), (_width / 2), (_height / 2));
}