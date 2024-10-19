#include "hbpch.h"

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"

bool HoneyBadger::Engine::Init()
{
	HoneyBadger::Dispatcher::Init();

	return true;
}
