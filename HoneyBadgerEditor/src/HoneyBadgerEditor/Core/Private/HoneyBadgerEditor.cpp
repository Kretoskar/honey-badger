#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"

#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"

bool HoneyBadgerEditor::Editor::Init()
{
	if (!_engine.Init())
	{
		return false;
	}

	HoneyBadger::WindowInitSettings WindowInitSettings
	{
		"Honey Badger Editor",
		HoneyBadger::WindowState::Maximized,
		1920, 
		1080,
		1.0f / 6.0f,
		1.0f / 6.0f,
		1.0f / 14.0f,
		1.0f / 4.0f
	};

	if (!_window.Init(WindowInitSettings))
	{
		return false;
	}

	if (!_engine.InitAfterWindow())
	{
		return false;
	}

	if (!_ui.Init(_window.GetGlfwWindow()))
	{
		return false;
	}

	_camera = std::make_shared<HoneyBadger::Camera>(&_window, HoneyBadger::Vec3(1.0f, 1.0f, 1.0f));
	_camera->Init();
	_debugRenderer = std::make_shared<HoneyBadger::DebugRenderer>(_camera);
	_debugRenderer->Init();

	_assetsRegistry = std::make_shared<HoneyBadger::AssetsRegistry>();
	_assetsRegistry->Init();

	// TODO: fix
	_scene = std::make_shared<HoneyBadger::Scene>(_assetsRegistry.get());
	_ecs = std::make_shared<HoneyBadger::ECS>();


	_ecs->RegisterComponent<HoneyBadger::TransformComponent>();
	_ecs->RegisterComponent<HoneyBadger::MeshComponent>();



	_renderingSystem.Init(_camera.get());

	_ecs->RegisterSystem(&_renderingSystem);
	_ecs->RegisterComponentInSystem<HoneyBadger::TransformComponent>(_renderingSystem);
	_ecs->RegisterComponentInSystem<HoneyBadger::MeshComponent>(_renderingSystem);

	HoneyBadger::Entity e = _ecs->CreateEntity();
	HoneyBadger::TransformComponent& tc = _ecs->AddComponent<HoneyBadger::TransformComponent>(e);
	HoneyBadger::MeshComponent& mc = _ecs->AddComponent<HoneyBadger::MeshComponent>(e);
	mc.Mesh = _assetsRegistry->Plane.get();
	tc.Scale = tc.Scale * 0.1f;
	tc.Rotation = HoneyBadger::Quat(3.14f / 2, { 1.0f, 0.0f, 0.0f });


	return true;
}
void HoneyBadgerEditor::Editor::Start()
{
	while (!_shouldClose && !_window.GetShouldClose())
	{
		_camera->Update();

		_ui.CreateFrame();
		_ui.Render();
		_renderingSystem.Render();
		_debugRenderer->Render();
		_window.Update();
	}

	ShutDown_Internal();
}

void HoneyBadgerEditor::Editor::ShutDown()
{
	_shouldClose = true;
}

void HoneyBadgerEditor::Editor::ShutDown_Internal()
{
	_window.Shutdown();
}