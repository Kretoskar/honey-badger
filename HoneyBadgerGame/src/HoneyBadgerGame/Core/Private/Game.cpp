#include "HoneyBadgerGame/Core/Public/Game.h"
#include "HoneyBadgerCore/ECS/Public/Components/Components.h"

bool HoneyBadgerGame::Game::Init(HoneyBadger::HBString name, HoneyBadger::HBString startSceneName)
{
	if (!_engine.Init())
	{
		return false;
	}

	HoneyBadger::WindowInitSettings WindowInitSettings
	{
		name,
		HoneyBadger::WindowState::Fullscreen,
		2560,
		1440,
		0,0,0,0	
	};

	if (!_window.Init(WindowInitSettings))
	{
		return false;
	}

	if (!_engine.InitAfterWindow())
	{
		return false;
	}

	_camera = std::make_shared<HoneyBadger::Camera>(&_window, HoneyBadger::Vec3(1.0f, 1.0f, 1.0f));
	_camera->Init();

	_ecs = std::make_shared<HoneyBadger::ECS>();

	HoneyBadger::Components::RegisterAllComponents(*_ecs);

	_renderingSystem.Register(*_ecs, _camera.get());
	_modelRenderingSystem.Register(*_ecs, _camera.get());
	_lightRenderingSystem.Register(*_ecs, _camera.get());

	if (auto scene = HoneyBadger::AssetsRegistry::Instance->GetSceneByName(startSceneName))
	{
		scene->InitECS(*_ecs);
	}
	else
	{
		return false;
	}

	for (HoneyBadger::Entity entity : _ecs->LivingEntities)
	{
		HoneyBadger::NameComponent* nameComp = _ecs->GetComponentPtr<HoneyBadger::NameComponent>(entity);
		if (nameComp)
		{
			NameEntityMap.emplace(nameComp->Name, entity);
		}
	}

	return true;
}

void HoneyBadgerGame::Game::Start()
{
	BeginPlay();
	while (!_shouldClose && !_window.GetShouldClose())
	{
		Tick();

		_camera->Update();

		_lightRenderingSystem.UpdateShaders();
		_renderingSystem.Render();
		_modelRenderingSystem.Render();

		_window.Update();
	}
	EndPlay();
}

void HoneyBadgerGame::Game::ShutDown()
{
	_shouldClose = true;
}

HoneyBadger::Entity HoneyBadgerGame::Game::GetEntityByName(HoneyBadger::HBString Name)
{
	return NameEntityMap[Name];
}

void HoneyBadgerGame::Game::BeginPlay()
{
	BeginPlay_Internal();
}

void HoneyBadgerGame::Game::Tick()
{
	Tick_Internal();
}

void HoneyBadgerGame::Game::EndPlay()
{
	_window.Shutdown();
}