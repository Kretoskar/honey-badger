#include "HoneyBadgerGame/Core/Public/Game.h"

bool HoneyBadgerGame::Game::Init(HoneyBadger::HBString name)
{
	HoneyBadger::WindowInitSettings WindowInitSettings
	{
		name,
		HoneyBadger::WindowState::Fullscreen,
		1920,
		1080,
		0,0,0,0	
	};
	return _engine.Init() && _window.Init(WindowInitSettings) && Init_Internal();
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