#pragma once

#include <memory>

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"

#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/ECS/Public/Systems/RenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/ModelRenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/LightingSystem.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"

namespace HoneyBadgerGame
{
	class Game
	{
	public:
	
		bool Init(HoneyBadger::HBString name, HoneyBadger::HBString startSceneName);
		void Start();
		void ShutDown();

	protected:
		virtual bool Init_Internal() = 0;
		virtual void BeginPlay_Internal() = 0;
		virtual void Tick_Internal() = 0;
		virtual void EndPlay_Internal() = 0;

	private:
		void BeginPlay();
		void Tick();
		void EndPlay();

		bool _shouldClose = false;

		HoneyBadger::Engine _engine;
		HoneyBadger::Window _window;

		std::shared_ptr<HoneyBadger::Camera> _camera;
		std::shared_ptr<HoneyBadger::ECS> _ecs;

		HoneyBadger::RenderingSystem _renderingSystem;
		HoneyBadger::ModelRenderingSystem _modelRenderingSystem;
		HoneyBadger::LightRenderingSystem _lightRenderingSystem;
	};
}