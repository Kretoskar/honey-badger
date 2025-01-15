#include "Sandbox/Core/Public/Sandbox.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Math/Public/MathCore.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

using namespace HoneyBadger;

float carFwdSpeed = 250.0f;
float carBwdSpeed = 250.0f;
float steeringSpeed = 0.6f;
float maxSteeringYaw = 0.0006f;
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
	carFrontEntity = GetEntityByName("carFront");

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

	//camera
	TransformComponent& camArmTc = _ecs->GetComponent<TransformComponent>(camArmEntity);
	camArmTc.Position = Vec3::Lerp(camArmTc.Position, carTc.Position, 0.01f);
	camArmTc.Position.y += 0.0005f;
	camArmTc.Rotation = carTc.Rotation;

	//car
	TransformComponent& carFrontTc = _ecs->GetComponent<TransformComponent>(carFrontEntity);

	CollisionResult frontRes = _physicsSystem.Raycast(
		carFrontTc.WorldMatrix.position.ToVec3() + Vec3(0.0f, 1.0f, 0.0f) * 0.0035f,
		carFrontTc.WorldMatrix.position.ToVec3() + Vec3(0.0f, 1.0f, 0.0f) * -0.0035f);

	carVelocity += Vec3(0.0f, -4.0f * deltaTime, 0.0f);

	CollisionResult res = _physicsSystem.Raycast(
		carTc.WorldMatrix.position.ToVec3() + Vec3(0.0f, 1.0f, 0.0f) * 0.0035f,
		carTc.WorldMatrix.position.ToVec3() + Vec3(0.0f, 1.0f, 0.0f) * -0.0035f);

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

	if (frontRes.wasCollision)
	{
		float dist = Vec3::Distance(frontRes.hitLocation, carTc.Position);
		float yDiff = std::fabsf(frontRes.hitLocation.y - carTc.Position.y);
		float rot = std::asin(yDiff / dist);

		if (frontRes.hitLocation.y > carTc.Position.y)
		{
			carTc.Rotation = carTc.Rotation * Quat(rot / 100.0f, carTc.WorldMatrix.right.ToVec3());
		}
		else 
		{
			carTc.Rotation = carTc.Rotation * Quat(deltaTime * 5000.0f, carTc.WorldMatrix.right.ToVec3());
		}
		//frontRes.hitLocation.y
	}
	else if (!res.wasCollision)
	{
		carTc.Rotation = carTc.Rotation * Quat(deltaTime * -1000.0f, carTc.WorldMatrix.right.ToVec3());
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

	float speedAdjustedMaxSteeringYaw = MathCore::Lerp(maxSteeringYaw * 2.0f, maxSteeringYaw, a);

	if (rightPressed)
	{
		if (TireYaw > 0.0f)
		{
			TireYaw = 0.0f;
		}

		TireYaw = 
			MathCore::Clamp(TireYaw - steeringSpeed * deltaTime, -speedAdjustedMaxSteeringYaw, speedAdjustedMaxSteeringYaw);
	}
	else if (leftPressed)
	{
		if (TireYaw < 0.0f)
		{
			TireYaw = 0.0f;
		}

		TireYaw = 
			MathCore::Clamp(TireYaw + steeringSpeed * deltaTime, -speedAdjustedMaxSteeringYaw, speedAdjustedMaxSteeringYaw);;
	}
	else 
	{
		TireYaw = MathCore::Lerp(TireYaw, 0.0f, 0.01f);
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
