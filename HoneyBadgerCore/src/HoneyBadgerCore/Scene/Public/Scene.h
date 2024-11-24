#pragma once

#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"

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

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneData, Guid, TransformComponentMap, MeshComponentMap)
	};

	class Scene
	{
	public:
		Scene() = default;
		Scene(const SceneData& InData) : Data(InData) {};
		Scene(ECS& Ecs);

		SceneData Data;
	};
}