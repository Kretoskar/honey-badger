#include "Sandbox/Core/Public/Sandbox.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

#include "HoneyBadgerCore/Window/Public/Window.h"

using namespace HoneyBadger;

float carFwdSpeed = 450.0f;
float carBwdSpeed = 450.0f;

bool Sand::CarGame::Init_Internal()
{
	std::shared_ptr<Sand::SandboxCamera> sandboxCam = std::make_shared<Sand::SandboxCamera>(&_window, HoneyBadger::Vec3());
	sandboxCam->Init(_ecs, this);

	_camera = sandboxCam;

	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_PRESS, 0), OnForwardPressed)
	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_W, GLFW_RELEASE, 0), OnForwardReleased)

	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_PRESS, 0), OnBackwardPressed)
	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_S, GLFW_RELEASE, 0), OnBackwardReleased)

	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_PRESS, 0), OnRightPressed)
	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_D, GLFW_RELEASE, 0), OnRightReleased)

	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_PRESS, 0), OnLeftPressed)
	HB_BIND_EVENT(KeyboardEvent::Type(GLFW_KEY_A, GLFW_RELEASE, 0), OnLeftReleased)

	return true;
}

void Sand::CarGame::BeginPlay_Internal()
{
	camEntity = GetEntityByName("cam");
	camArmEntity = GetEntityByName("camArm");
	carEntity = GetEntityByName("car");

	frontLeftTireEntity = GetEntityByName("carTireFrontLeft");
	backLeftTireEntity = GetEntityByName("carTireBackLeft");
	frontRightTireEntity = GetEntityByName("carTireFrontRight");
	backRightTireEntity = GetEntityByName("carTireBackRight");

	TransformComponent& carTc = _ecs->GetComponent<TransformComponent>(carEntity);
	TransformComponent& tireTc = _ecs->GetComponent<TransformComponent>(frontLeftTireEntity);
	TransformComponent& backTireTc = _ecs->GetComponent<TransformComponent>(backLeftTireEntity);
	
	tireToCar = carTc.Position - tireTc.Position;
	tireToTireLen = (tireTc.Position - backTireTc.Position).Len();

	TransformComponent& frontRightTireTc = _ecs->GetComponent<TransformComponent>(frontRightTireEntity);
	TransformComponent& backRightTireTc = _ecs->GetComponent<TransformComponent>(backRightTireEntity);

	blTireToBRTire = backRightTireTc.Position - backTireTc.Position;
	flTireToFRTire = frontRightTireTc.Position - tireTc.Position;
}

void Sand::CarGame::TickPrePhysics_Internal(float deltaTime)
{
	HB_LOG_ERROR("chuuuuj")
	HandleInput();
}

void Sand::CarGame::TickPostPhysics_Internal(float deltaTime)
{
	TransformComponent& carTc = _ecs->GetComponent<TransformComponent>(carEntity);
	TransformComponent& frontTireTc = _ecs->GetComponent<TransformComponent>(frontLeftTireEntity);
	TransformComponent& backTireTc = _ecs->GetComponent<TransformComponent>(backLeftTireEntity);

	carTc.Position = frontTireTc.Position + tireToCar;
	carTc.Rotation = backTireTc.Rotation * Quat(3.1415f, Vec3(0.0f, 1.0f, 0.0f));
	
	Vec3 frontToBackTire = backTireTc.Position - frontTireTc.Position;
	backTireTc.Position = frontTireTc.Position + frontToBackTire.Normalized() * tireToTireLen;

	TransformComponent& frontRightTireTc = _ecs->GetComponent<TransformComponent>(frontRightTireEntity);
	TransformComponent& backRightTireTc = _ecs->GetComponent<TransformComponent>(backRightTireEntity);

	frontRightTireTc.Position = frontTireTc.Position + flTireToFRTire;
	backRightTireTc.Position = backTireTc.Position + blTireToBRTire;

	float angle = std::asin((backTireTc.Position.y - frontTireTc.Position.y) / tireToTireLen);
	carTc.Rotation = carTc.Rotation * Quat(angle, backTireTc.WorldMatrix.right.ToVec3());
	carTc.Position = carTc.Position + carTc.WorldMatrix.up.ToVec3() * angle * 10.0f;
}

void Sand::CarGame::EndPlay_Internal()
{
}

void Sand::CarGame::HandleInput()
{
	RigidbodyComponent& rbComp = _ecs->GetComponent<RigidbodyComponent>(frontLeftTireEntity);
	TransformComponent& frontTireTc = _ecs->GetComponent<TransformComponent>(frontLeftTireEntity);

	//TODO:
	// static Vec3 velocity;
	// rotate this velocity with tire's quat

	if (forwardPressed)
	{
		rbComp.Forces.push_back(frontTireTc.WorldMatrix.forward.ToVec3() * carFwdSpeed);
	}
	else if (backwardPressed)
	{
		rbComp.Forces.push_back(frontTireTc.WorldMatrix.forward.ToVec3() * -carFwdSpeed);
	}

	if (rightPressed)
	{
		frontTireTc.Rotation = frontTireTc.Rotation * Quat(-0.001f, Vec3(0.0f, 1.0f, 0.0f));
	}
	else if (leftPressed)
	{
		frontTireTc.Rotation = frontTireTc.Rotation * Quat(0.001f, Vec3(0.0f, 1.0f, 0.0f));
	}
}

void Sand::CarGame::OnForwardPressed(void* payload)
{
	forwardPressed = true;
}

void Sand::CarGame::OnForwardReleased(void* payload)
{
	forwardPressed = false;
}

void Sand::CarGame::OnBackwardPressed(void* payload)
{
	backwardPressed = true;
}

void Sand::CarGame::OnBackwardReleased(void* payload)
{
	backwardPressed = false;
}

void Sand::CarGame::OnRightPressed(void* payload)
{
	rightPressed = true;
}

void Sand::CarGame::OnRightReleased(void* payload)
{
	rightPressed = false;
}

void Sand::CarGame::OnLeftPressed(void* payload)
{
	leftPressed = true;
}

void Sand::CarGame::OnLeftReleased(void* payload)
{
	leftPressed = false;
}
