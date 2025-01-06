#pragma once

#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/ModelComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/DirectionalLightComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/RigidbodyComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/SphereColliderComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/BoxCollisionComponent.h"

#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	class AssetsRegistry;

	struct SceneData
	{
		SceneData()
		{
		}

		std::string Guid;
		std::map<unsigned, TransformComponent> TransformComponentMap;
		std::map<unsigned, MeshComponent> MeshComponentMap;
		std::map<unsigned, NameComponent> NameComponentMap;
		std::map<unsigned, ModelComponent> ModelComponentMap;
		std::map<unsigned, DirectionalLightComponent> DirectionalLightComponentMap;
		std::map<unsigned, RigidbodyComponent> RigidbodyComponentMap;
		std::map<unsigned, SphereColliderComponent> SphereColliderComponentMap;
		std::map<unsigned, BoxCollisionComponent> BoxCollisionComponentMap;
		std::vector<Entity> Entities;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneData, Guid, TransformComponentMap, MeshComponentMap, NameComponentMap, ModelComponentMap, DirectionalLightComponentMap, RigidbodyComponentMap, SphereColliderComponentMap, BoxCollisionComponentMap, Entities)
	};

	class Scene
	{
	public:
		Scene() = default;
		Scene(const SceneData& InData) : Data(InData) {};
		Scene(ECS& Ecs);

		void InitECS(ECS& Ecs);

		SceneData Data;
	};
}