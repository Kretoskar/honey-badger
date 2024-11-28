#include "hbpch.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"

HoneyBadger::Scene::Scene(ECS& Ecs)
{
	Data.Guid = GenerateGUID();

	for (Entity e : Ecs.LivingEntities)
	{
		Data.Entities.push_back(e);

		// TODO: Rewrite this
		if (TransformComponent* tc = Ecs.GetComponentPtr<TransformComponent>(e))
		{
			Data.TransformComponentMap[e] = *tc;
		}

		if (MeshComponent* mc = Ecs.GetComponentPtr<MeshComponent>(e))
		{
			Data.MeshComponentMap[e] = *mc;
		}

		if (NameComponent* nc = Ecs.GetComponentPtr<NameComponent>(e))
		{
			Data.NameComponentMap[e] = *nc;
		}
	}
}

void HoneyBadger::Scene::InitECS(ECS& Ecs)
{
	for (Entity e : Data.Entities)
	{
		Entity newE = Ecs.CreateEntity();
		if (Data.TransformComponentMap.find(e) != Data.TransformComponentMap.end())
		{
			TransformComponent& tc = Ecs.AddComponent<TransformComponent>(newE);
			tc = Data.TransformComponentMap[e];
		}

		if (Data.MeshComponentMap.find(e) != Data.MeshComponentMap.end())
		{
			MeshComponent& mc = Ecs.AddComponent<MeshComponent>(newE);
			mc = Data.MeshComponentMap[e];
		}

		if (Data.NameComponentMap.find(e) != Data.NameComponentMap.end())
		{
			NameComponent & nc = Ecs.AddComponent<NameComponent>(newE);
			nc = Data.NameComponentMap[e];
		}
	}
}
