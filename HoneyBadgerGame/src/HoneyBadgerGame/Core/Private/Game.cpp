#include "HoneyBadgerGame/Core/Public/Game.h"

bool HoneyBadgerGame::Game::Init(uint32_t width, uint32_t height, HoneyBadger::HBString name)
{
	return _engine.Init() && _window.Init(width, height, name) && Init_Internal();
}

void HoneyBadgerGame::Game::Start()
{
	BeginPlay();
	while (!_shouldClose && !_window.GetShouldClose())
	{
		Tick();
	}
	EndPlay();
}

void HoneyBadgerGame::Game::ShutDown()
{
	_shouldClose = true;
}

void HoneyBadgerGame::Game::BeginPlay()
{
	BeginPlay_Internal();
}

void HoneyBadgerGame::Game::Tick()
{
	Tick_Internal();

	_window.Update();
}

void HoneyBadgerGame::Game::EndPlay()
{
	_window.Shutdown();
}