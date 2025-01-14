#include "Sandbox/Core/Public/Sandbox.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

using namespace HoneyBadger;

float carFwdSpeed = 250.0f;
float carBwdSpeed = 250.0f;
float steeringSpeed = 100.0f;
float maxCarSpeed = 0.005f;

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
}

void Sand::CarGame::TickPrePhysics_Internal(float deltaTime)
{
	HandleInput(deltaTime);
}

void Sand::CarGame::TickPostPhysics_Internal(float deltaTime)
{
	TransformComponent& carTc = _ecs->GetComponent<TransformComponent>(carEntity);
	
	carVelocity += Vec3(0.0f, -1.0f * deltaTime, 0.0f);

	CollisionResult res = _physicsSystem.Raycast(
		carTc.WorldMatrix.position.ToVec3() + carTc.WorldMatrix.up.ToVec3() * 0.35f,
		carTc.WorldMatrix.position.ToVec3() + carTc.WorldMatrix.up.ToVec3() * -0.35f);

	if (res.wasCollision)
	{
		//if (Vec3::Distance(res.hitLocation, carTc.WorldMatrix.position.ToVec3()) < 0.015f)
		{
			float dot = Vec3::Dot(carVelocity, res.hitSurfaceNormal);
			Vec3 HitVec = Vec3::Project(carVelocity, res.hitSurfaceNormal);
			carVelocity -= HitVec;

			//HB_LOG_ERROR("car %f %f %f", carTc.WorldMatrix.position.ToVec3().x, carTc.WorldMatrix.position.ToVec3().y, carTc.WorldMatrix.position.ToVec3().z)
			//carVelocity = 
			//	Vec3::Reflect(carVelocity, res.hitSurfaceNormal) * 
			//	MathCore::Lerp(0.5f, 1.0f, std::fabsf(dot));
		}
	}
	float cachedCarYVelocity = carVelocity.y;
	Vec3 carVelocity2D = Vec3(carVelocity.x, 0.0f, carVelocity.z);
	carVelocity2D = Vec3::Lerp(Vec3(), carVelocity2D, 0.999f);
	carVelocity2D.y = cachedCarYVelocity;
	carVelocity = carVelocity2D;

	Quat rotThisFrame = Quat(TireYaw * 10.0f, Vec3(0.0f, 1.0f, 0.0f));
	carVelocity = rotThisFrame * carVelocity;
	carTc.Rotation = carTc.Rotation * rotThisFrame;
	carTc.Position += carVelocity;
}

void Sand::CarGame::EndPlay_Internal()
{
}

void Sand::CarGame::HandleInput(float deltaTime)
{
	TransformComponent& carTc = _ecs->GetComponent<TransformComponent>(carEntity);
	float Speed = carVelocity.Len();

	if (forwardPressed)
	{
		if (Speed < maxCarSpeed * 1.0f)
		{
			carVelocity -= carTc.WorldMatrix.forward.ToVec3() * carFwdSpeed * deltaTime;
		}
	}
	else if (backwardPressed)
	{
		if (Speed < maxCarSpeed * 1.0f)
		{
			carVelocity += carTc.WorldMatrix.forward.ToVec3() * carBwdSpeed * deltaTime;
		}
	}

	float a = 1 - (Speed / maxCarSpeed);

	float speedAdjustedSteeringSpeed = MathCore::Lerp(steeringSpeed * 2.0f, steeringSpeed, a);

	if (rightPressed)
	{
		TireYaw = -speedAdjustedSteeringSpeed * deltaTime;
	}
	else if (leftPressed)
	{
		TireYaw = speedAdjustedSteeringSpeed * deltaTime;
	}
	else
	{
		TireYaw = 0.0f;
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
