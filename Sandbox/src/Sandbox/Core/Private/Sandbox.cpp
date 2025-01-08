#include "Sandbox/Core/Public/Sandbox.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

using namespace HoneyBadger;

bool Sand::CarGame::Init_Internal()
{
	std::shared_ptr<Sand::SandboxCamera> sandboxCam = std::make_shared<Sand::SandboxCamera>(&_window, HoneyBadger::Vec3());
	sandboxCam->Init(_ecs, this);

	_camera = sandboxCam;

	return true;
}

void Sand::CarGame::BeginPlay_Internal()
{
	camEntity = GetEntityByName("cam");
	camArmEntity = GetEntityByName("camArm");
	carEntity = GetEntityByName("car");
	frontLeftTireEntity = GetEntityByName("carTireFrontLeft");
	backLeftTireEntity = GetEntityByName("carTireBackLeft");

	TransformComponent& carTc = _ecs->GetComponent<TransformComponent>(carEntity);
	TransformComponent& tireTc = _ecs->GetComponent<TransformComponent>(frontLeftTireEntity);
	
	tireToCar = carTc.Position - tireTc.Position;
}

void Sand::CarGame::Tick_Internal(float deltaTime)
{
	TransformComponent& carTc = _ecs->GetComponent<TransformComponent>(carEntity);
	TransformComponent& frontTireTc = _ecs->GetComponent<TransformComponent>(frontLeftTireEntity);
	TransformComponent& backTireTc = _ecs->GetComponent<TransformComponent>(frontLeftTireEntity);

	carTc.Position = frontTireTc.Position + tireToCar;
	//carTc.Rotation = HoneyBadger::Mat4::LookAt(frontTireTc.Position, backTireTc.Position, Vec3(0.0f, 1.0f, 0.0f) )
	
}

void Sand::CarGame::EndPlay_Internal()
{
}