#pragma once

#include <memory>
#include <unordered_map>

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"

#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/ECS/Public/Systems/RenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/ModelRenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/TransformSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/LightingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Systems/PhysicsSystem.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"
#include <HoneyBadgerCore/Rendering/Public/Skybox.h>

namespace HoneyBadgerGame
{
	class Game
	{
	public:
	
		bool Init(HoneyBadger::HBString name, HoneyBadger::HBString startSceneName);
		void Start();
		void ShutDown();

		HoneyBadger::Entity GetEntityByName(std::string Name);

	protected:
		virtual bool Init_Internal() = 0;
		virtual void BeginPlay_Internal() = 0;
		virtual void TickPrePhysics_Internal(float deltaTime) = 0;
		virtual void TickPostPhysics_Internal(float deltaTime) = 0;
		virtual void EndPlay_Internal() = 0;

		std::shared_ptr<HoneyBadger::ECS> _ecs;
		std::shared_ptr<HoneyBadger::Camera> _camera;
		HoneyBadger::Window _window;

	private:
		void BeginPlay();
		void TickPrePhysics(float deltaTime);
		void TickPostPhysics(float deltaTime);
		void EndPlay();

		bool _shouldClose = false;

		HoneyBadger::Engine _engine;

		HoneyBadger::RenderingSystem _renderingSystem;
		HoneyBadger::ModelRenderingSystem _modelRenderingSystem;
		HoneyBadger::LightRenderingSystem _lightRenderingSystem;
		HoneyBadger::TransformSystem _transformSystem;
		HoneyBadger::PhysicsSystem _physicsSystem;
		HoneyBadger::Skybox _skybox;

		std::unordered_map<std::string, HoneyBadger::Entity> NameEntityMap;
	};
}