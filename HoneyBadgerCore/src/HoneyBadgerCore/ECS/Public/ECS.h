#pragma once

#include <queue>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <bitset>
#include <vector>
#include <set>

#include "HoneyBadgerCore/ECS/Public/ECSTypes.h"
#include "HoneyBadgerCore/ECS/Public/ComponentArray.h"
#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadger
{
	class ECS
	{
	public:
		ECS();


		template <typename T>
		void RegisterComponent()
		{
			CompNameToType[typeid(T).name()] = CurrComponentType;
			CurrComponentType++;
			ComponentArrays.insert({ typeid(T).name(), std::make_shared<ComponentArray<T>>() });
		}

		Entity CreateEntity();

		void DestroyEntity(Entity entity);

		template<typename T>
		T& GetComponent(Entity e)
		{
			std::shared_ptr<ComponentArray<T>> compArray = GetComponentArray<T>(typeid(T).name());
			return compArray->GetData(e);
		}

		template<typename T>
		T* GetComponentPtr(Entity e)
		{
			std::shared_ptr<ComponentArray<T>> compArray = GetComponentArray<T>(typeid(T).name());
			return compArray->GetDataPtr(e);
		}

		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray(HBString name)
		{
			return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[name]);
		}

		template <typename T>
		T& AddComponent(Entity entity)
		{
			ComponentType compType = CompNameToType[typeid(T).name()];

			Signatures[entity].set(compType, true);

			GetComponentArray<T>(typeid(T).name())->Insert(entity, T());

			for (System* system : Systems)
			{
				if ((system->_sig & Signatures[entity]) == system->_sig)
				{
					system->_entities.insert(entity);
				}
			}

			return GetComponent<T>(entity);
		}

		void RegisterSystem(System* system);

		void RemoveComponent(Entity entity, ComponentType compType);

		template <typename T>
		void RegisterComponentInSystem(System& system)
		{
			system._sig.set(CompNameToType[typeid(T).name()], true);
		}
		
		std::queue<Entity> AvailableEntities{};
		std::array<Signature, MAX_ENTITIES> Signatures {};
		Entity LivingEntityCount{};

		std::vector<System*> Systems{};
		// dynamic size, but reserves max entity count
		std::unordered_set<Entity> LivingEntities{};

		ComponentType CurrComponentType{};
		std::unordered_map<HBString, ComponentType, HBString::HBStringHasher> CompNameToType{};
		std::unordered_map<HBString, std::shared_ptr<IComponentArray>, HBString::HBStringHasher> ComponentArrays{};
	};
}