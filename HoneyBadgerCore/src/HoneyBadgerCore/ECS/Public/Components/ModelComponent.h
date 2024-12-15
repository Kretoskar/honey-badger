#pragma once

#pragma once

#include <vector>
#include <string>
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	struct ModelComponent
	{
		std::string Guid;
		std::vector<std::string> MaterialsGuids;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ModelComponent, Guid, MaterialsGuids)
		RTTI_DECLARE(ModelComponent)
	};
}