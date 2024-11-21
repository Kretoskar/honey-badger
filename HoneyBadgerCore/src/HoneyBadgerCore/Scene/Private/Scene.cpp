#include "hbpch.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"

#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"

#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"

HoneyBadger::Scene::Scene(AssetsRegistry* assetsRegistry)
{
	_sceneEcs.RegisterComponent<TransformComponent>();
	_sceneEcs.RegisterComponent<MeshComponent>();

	HoneyBadger::Entity e = _sceneEcs.CreateEntity();
	TransformComponent& tc = _sceneEcs.AddComponent<TransformComponent>(e);
	MeshComponent& mc = _sceneEcs.AddComponent<MeshComponent>(e);
	mc.Mesh = assetsRegistry->GetMeshByName("Plane").get();
}