#include "HoneyBadgerGame/Core/Public/Game.h"
#include "HoneyBadgerCore/ECS/Public/Components/Components.h"
#include <chrono>
#include <ctime>   

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

	_ecs = std::make_shared<HoneyBadger::ECS>();

	HoneyBadger::Components::RegisterAllComponents(*_ecs);

	Init_Internal();

	_transformSystem.Register(*_ecs);
	_renderingSystem.Register(*_ecs, _camera.get());
	_modelRenderingSystem.Register(*_ecs, _camera.get());
	_lightRenderingSystem.Register(*_ecs, _camera.get());
	_physicsSystem.Register(*_ecs);

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

	_skybox.Init(_camera.get());

	return true;
}

void HoneyBadgerGame::Game::Start()
{
	static float deltaTime = 0.0f;
	BeginPlay();
	while (!_shouldClose && !_window.GetShouldClose())
	{
		auto start = std::chrono::system_clock::now();
		Tick(deltaTime);

		_transformSystem.UpdateWorldTransforms();
		
		HoneyBadger::Entity ground = GetEntityByName("Ground");
		HoneyBadger::Entity sphere = GetEntityByName("sphere");

		_physicsSystem.Update(deltaTime);

		_camera->Update();

		_lightRenderingSystem.UpdateShaders();
		_renderingSystem.Render();
		_modelRenderingSystem.Render();
		_skybox.Render();
		_window.Update();

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = end - start;
		deltaTime = elapsed_seconds.count() / 1000.0f;
	}
	EndPlay();
}

void HoneyBadgerGame::Game::ShutDown()
{
	_shouldClose = true;
}

HoneyBadger::Entity HoneyBadgerGame::Game::GetEntityByName(std::string Name)
{
	return NameEntityMap.find(Name) != NameEntityMap.end() ? NameEntityMap[Name] : -1;
}

void HoneyBadgerGame::Game::BeginPlay()
{
	BeginPlay_Internal();
}

void HoneyBadgerGame::Game::Tick(float deltaTime)
{
	Tick_Internal(deltaTime);
}

void HoneyBadgerGame::Game::EndPlay()
{
	_window.Shutdown();
}