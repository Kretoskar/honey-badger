#pragma once

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/Rendering/Public/DebugRenderer.h"
#include "HoneyBadgerCore/Rendering/Public/Skybox.h"
#include "HoneyBadgerEditor/Core/Public/EditorUI.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"
#include "HoneyBadgerCore/ECS/Public/Systems/RenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/ModelRenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/LightingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/TransformSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/ColliderRenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/BoxCollisionRenderingSystem.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerEditor/Systems/Public/EditorUISystem.h"

#include <memory>

namespace HoneyBadgerEditor
{
	class Editor
	{
	public:
		bool Init();
		void Start();
		void ShutDown();

		void LoadScene(const char* name);
		void SaveScene(const char* name);
		void NewEntity();

		std::shared_ptr<HoneyBadger::ECS> GetECS() const { return _ecs; }

	private:
		void ShutDown_Internal();

		bool _shouldClose = false;

		HoneyBadger::Engine _engine;
		HoneyBadger::Window _window;
		HoneyBadgerEditor::EditorUI _ui;

		std::shared_ptr<HoneyBadger::Camera> _camera;
		std::shared_ptr<HoneyBadger::DebugRenderer> _debugRenderer;

		std::shared_ptr<HoneyBadger::ECS> _ecs;

		HoneyBadger::RenderingSystem _renderingSystem;
		HoneyBadger::ModelRenderingSystem _modelRenderingSystem;
		HoneyBadger::LightRenderingSystem _lightRenderingSystem;
		HoneyBadger::TransformSystem _transformSystem;
		HoneyBadger::ColliderRenderingSystem _colliderRenderingSystem;
		HoneyBadger::BoxCollisionRenderingSystem _boxCollisionRenderingSystem;
		HoneyBadger::Skybox _skybox;
		HoneyBadgerEditor::EditorUISystem _uiSystem;
	};
}