#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	ECS::ECS()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			AvailableEntities.push(entity);
		}
	}

	Entity ECS::CreateEntity()
	{
		Entity id = AvailableEntities.front();
		AvailableEntities.pop();
		LivingEntityCount++;

		return id;
	}

	void ECS::DestroyEntity(Entity entity)
	{
		Signatures[entity].reset();
		AvailableEntities.push(entity);
		LivingEntityCount--;

		for (auto CompArrayPair : ComponentArrays)
		{
			CompArrayPair.second->EntityDestroyed(entity);
		}

		for (System* system : Systems)
		{
			system->_entities.erase(entity);
		}
	}

	void ECS::RegisterSystem(System* system)
	{
		Systems.push_back(system);
		system->_ecs = this;

		// TODO: iterate over signatures
	}

	void ECS::RemoveComponent(Entity entity, ComponentType compType)
	{
		Signatures[entity].set(compType, false);

		for (System* system : Systems)
		{
			system->_entities.erase(entity);

			if ((system->_sig & Signatures[entity]) == Signatures[entity])
			{
				system->_entities.insert(entity);
			}
		}
	}
}