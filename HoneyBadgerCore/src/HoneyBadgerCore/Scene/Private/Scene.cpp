#include "hbpch.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"

HoneyBadger::Scene::Scene(ECS& Ecs)
{
	Data.Guid = GenerateGUID();

	for (Entity e : Ecs.LivingEntities)
	{
		// TODO: Rewrite this
		if (TransformComponent* tc = Ecs.GetComponentPtr<TransformComponent>(e))
		{
			Data.TransformComponentMap[e] = *tc;
		}

		if (MeshComponent* mc = Ecs.GetComponentPtr<MeshComponent>(e))
		{
			Data.MeshComponentMap[e] = *mc;
		}
	}
}