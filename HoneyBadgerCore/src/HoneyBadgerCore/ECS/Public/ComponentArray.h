#pragma once

#include <vector>
#include <unordered_map>

#include "HoneyBadgerCore/ECS/Public/ECSTypes.h"

namespace HoneyBadger
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void Insert(Entity entity, T component)
		{
			size_t idx = componentArray.size();
			entityToIndexMap[entity] = idx;
			indexToEntityMap[idx] = entity;
			componentArray.push_back(component);
		}

		void Remove(Entity entity)
		{
			if (entityToIndexMap.find(entity) == entityToIndexMap.end())
			{
				return;
			}

			size_t Idx = entityToIndexMap[entity];
			T LastComp = componentArray.back();
			Entity LastEntity = indexToEntityMap[componentArray.size() - 1];

			entityToIndexMap.erase(entity);
			indexToEntityMap.erase(Idx);

			componentArray[Idx] = LastComp;
			componentArray.pop_back();


			entityToIndexMap[LastEntity] = Idx;
			indexToEntityMap[Idx] = LastEntity;
		}

		void EntityDestroyed(Entity entity) override
		{
			if (entityToIndexMap.find(entity) != entityToIndexMap.end())
			{
				Remove(entity);
			}
		}

		T& GetData(Entity entity)
		{
			return componentArray[entityToIndexMap[entity]];
		}

		T* GetDataPtr(Entity entity)
		{
			if (entityToIndexMap.find(entity) != entityToIndexMap.end())
			{
				if (componentArray.find(entityToIndexMap[entity]) != entityToIndexMap.end())
				{
					return componentArray[entityToIndexMap[entity]];
				}
			}

			return nullptr;
		}

		std::unordered_map<Entity, size_t> entityToIndexMap;
		std::unordered_map<size_t, Entity> indexToEntityMap;

		std::vector<T> componentArray;
	};
}