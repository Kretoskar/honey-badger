#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Systems/TransformSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"
#include "HoneyBadgerCore/Math/Public/Mat4.h"

using namespace HoneyBadger;

void TransformSystem::Register(ECS& ecs)
{
	REGISTER_SYSTEM()
	REGISTER_COMPONENT_IN_SYSTEM(TransformComponent)
}

void TransformSystem::UpdateWorldTransforms()
{
	std::unordered_map<HBString, TransformComponent*, HBString::HBStringHasher> EntityTransformMap;
	std::vector<HBString> EntityNames;
	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		NameComponent& nameComp = _ecs->GetComponent<NameComponent>(entity);
		EntityTransformMap.emplace(nameComp.Name, &transformComp);
		EntityNames.push_back(nameComp.Name);
	}

	TransformComponent::EntityNames = EntityNames;

	for (auto& entityPair : EntityTransformMap)
	{
		std::vector<TransformComponent*> parentChain;
		TransformComponent* currentTransformComp;
		currentTransformComp = entityPair.second;

		do 
		{
			parentChain.push_back(currentTransformComp);
			if (EntityTransformMap.find(currentTransformComp->Parent) != EntityTransformMap.end())
			{
				currentTransformComp = EntityTransformMap[currentTransformComp->Parent];
			}
			else
			{
				currentTransformComp = nullptr;
			}
			
		} while (currentTransformComp != nullptr);

		entityPair.second->WorldMatrix = parentChain[parentChain.size() - 1]->ToMat4();
		entityPair.second->WorldRotMatrix = parentChain[parentChain.size() - 1]->ToRotMat4();

		if (parentChain.size() > 1)
		{
			for (int32_t i = parentChain.size() - 2; i >= 0; --i)
			{
				entityPair.second->WorldMatrix = entityPair.second->WorldMatrix * parentChain[i]->ToMat4();
				entityPair.second->WorldRotMatrix = entityPair.second->WorldRotMatrix * parentChain[i]->ToRotMat4();
			}
		}
	}
}