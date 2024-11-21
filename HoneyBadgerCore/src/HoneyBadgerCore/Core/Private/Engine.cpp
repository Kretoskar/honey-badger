#include "hbpch.h"

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"

namespace HoneyBadger
{
	Engine* Engine::Instance = nullptr;

	bool HoneyBadger::Engine::Init()
	{
		Instance = this;

		HoneyBadger::Dispatcher::Init();

		return true;
	}

	bool HoneyBadger::Engine::InitAfterWindow()
	{
		AssetsReg = std::make_unique<AssetsRegistry>();
		AssetsReg->Init();

		return true;
	}
}