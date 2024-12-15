#pragma once

#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"

namespace HoneyBadger
{
	struct ModelData
	{
		std::string _guid;
		std::vector<std::string> _meshesGuids;
		// FixMe: Decouple transform from transform component
		std::vector<TransformComponent> _meshesLocalTransforms;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ModelData, _guid, _meshesGuids, _meshesLocalTransforms)
	};
}