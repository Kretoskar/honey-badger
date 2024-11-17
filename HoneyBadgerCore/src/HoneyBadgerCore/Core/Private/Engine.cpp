#include "hbpch.h"

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"

HoneyBadger::AssetsRegistry* HoneyBadger::Engine::AssetsReg = nullptr;

bool HoneyBadger::Engine::Init()
{
	HoneyBadger::Dispatcher::Init();

	return true;
}

bool HoneyBadger::Engine::InitAfterWindow()
{
	AssetsReg = new AssetsRegistry();
	AssetsReg->Init();

	return true;
}
