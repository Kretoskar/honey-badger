#include "Sandbox/Core/Public/Sandbox.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

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
	TransformComponent& backTireTc = _ecs->GetComponent<TransformComponent>(backLeftTireEntity);
	
	tireToCar = carTc.Position - tireTc.Position;
	tireToTireLen = (tireTc.Position - backTireTc.Position).Len();
}

void Sand::CarGame::Tick_Internal(float deltaTime)
{
	TransformComponent& carTc = _ecs->GetComponent<TransformComponent>(carEntity);
	TransformComponent& frontTireTc = _ecs->GetComponent<TransformComponent>(frontLeftTireEntity);
	TransformComponent& backTireTc = _ecs->GetComponent<TransformComponent>(backLeftTireEntity);

	RigidbodyComponent& rbComp = _ecs->GetComponent<RigidbodyComponent>(frontLeftTireEntity);

	rbComp.Forces.push_back(Vec3(0.0f, 0.0f, -0.5f));

	carTc.Position = frontTireTc.Position + tireToCar;
	carTc.Rotation = backTireTc.Rotation * Quat(3.1415f, Vec3(0.0f, 1.0f, 0.0f));
	
	Vec3 frontToBackTire = backTireTc.Position - frontTireTc.Position;
	backTireTc.Position = frontTireTc.Position + frontToBackTire.Normalized() * tireToTireLen;

	float angle = std::asin((backTireTc.Position.y - frontTireTc.Position.y) / tireToTireLen);
	HB_LOG_ERROR("%f", angle)
	carTc.Rotation = carTc.Rotation * Quat(angle, backTireTc.WorldMatrix.right.ToVec3());
}

void Sand::CarGame::EndPlay_Internal()
{
}