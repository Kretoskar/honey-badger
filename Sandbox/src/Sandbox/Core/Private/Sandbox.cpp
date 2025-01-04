#include "Sandbox/Core/Public/Sandbox.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

bool Sand::CarGame::Init_Internal()
{
	camEntity = GetEntityByName("cam");
	camArmEntity = GetEntityByName("camArm");

	std::shared_ptr<Sand::SandboxCamera> sandboxCam = std::make_shared<Sand::SandboxCamera>(&_window, HoneyBadger::Vec3());
	sandboxCam->Init(_ecs, this);

	_camera = sandboxCam;

	return true;
}

void Sand::CarGame::BeginPlay_Internal()
{
}

void Sand::CarGame::Tick_Internal(float deltaTime)
{
	
}

void Sand::CarGame::EndPlay_Internal()
{
}