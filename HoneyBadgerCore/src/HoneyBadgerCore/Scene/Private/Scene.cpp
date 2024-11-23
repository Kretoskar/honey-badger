#include "hbpch.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"

HoneyBadger::Scene::Scene(const ECS& Ecs)
{
	for (Entity e : Ecs.LivingEntities)
	{
		// TODO load from ECS here
	}
}