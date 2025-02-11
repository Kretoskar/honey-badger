#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"

#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"
#include <HoneyBadgerCore/ECS/Public/Components/Components.h>


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
		2560,
		1440,
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

	_ui.SetEditorUI(this);
	if (!_ui.Init(_window.GetGlfwWindow()))
	{
		return false;
	}

	_camera = std::make_shared<HoneyBadger::Camera>(&_window, HoneyBadger::Vec3(1.0f, 1.0f, 1.0f));
	_camera->Init();

	_debugRenderer = std::make_shared<HoneyBadger::DebugRenderer>(_camera);
	_debugRenderer->Init();

	_ecs = std::make_shared<HoneyBadger::ECS>();

	HoneyBadger::Components::RegisterAllComponents(*_ecs);

	_renderingSystem.Register(*_ecs, _camera.get());
	_modelRenderingSystem.Register(*_ecs, _camera.get());
	_lightRenderingSystem.Register(*_ecs, _camera.get());
	_uiSystem.Register(*_ecs, &_ui);
	_transformSystem.Register(*_ecs);
	_colliderRenderingSystem.Register(*_ecs, _camera.get());
	_boxCollisionRenderingSystem.Register(*_ecs, _camera.get());

	_skybox.Init(_camera.get());

	return true;
}
void HoneyBadgerEditor::Editor::Start()
{
	double prevTime = 0.0;
	double crntTime = 0.0;
	double deltaTime;

	while (!_shouldClose && !_window.GetShouldClose())
	{
		crntTime = glfwGetTime();
		deltaTime = (crntTime - prevTime) * 1000;

		// Resets times and counter
		prevTime = crntTime;

		_camera->Update();

		_transformSystem.UpdateWorldTransforms();
		_lightRenderingSystem.UpdateShaders();
		

		_colliderRenderingSystem.Render();
		_boxCollisionRenderingSystem.Render();
		_modelRenderingSystem.Render();
		_debugRenderer->Render();
		_skybox.Render();
		_renderingSystem.Render();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		_ui.CreateFrame(deltaTime);
		_ui.Render();
		_window.Update();
		_uiSystem.Update();
	}

	ShutDown_Internal();
}

void HoneyBadgerEditor::Editor::ShutDown()
{
	_shouldClose = true;
}

void HoneyBadgerEditor::Editor::LoadScene(const char* name)
{
	if (auto scene = HoneyBadger::AssetsRegistry::Instance->GetSceneByName(name))
	{
		scene->InitECS(*_ecs);

		//HoneyBadger::Entity e = _ecs->LivingEntities[0];
		//
		//HoneyBadger::NameComponent& nc = _ecs->AddComponent<HoneyBadger::NameComponent>();
		
		//nc.Name = "Plane";
	}
	else
	{
		HB_LOG_ERROR("Can't find scene with name %s", name)
	}
}

void HoneyBadgerEditor::Editor::SaveScene(const char* name)
{
	std::string path = "scenes\\";
	path += name;
	path += ".hbscene";

	HoneyBadger::File file(path.c_str());
	HoneyBadger::Scene s(*_ecs);
	nlohmann::json j = s.Data;
	file.OverrideContent(j.dump(4));
}

void HoneyBadgerEditor::Editor::NewEntity()
{
	HoneyBadger::Entity e = _ecs->CreateEntity();
	HoneyBadger::NameComponent& nc = _ecs->AddComponent<HoneyBadger::NameComponent>(e);
	nc.Name = "entity_" + std::to_string(_ecs->LivingEntityCount);
}

void HoneyBadgerEditor::Editor::ShutDown_Internal()
{
	_window.Shutdown();
}