#pragma once

#pragma once

#include <string>
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	struct ModelComponent
	{
		std::string Guid;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ModelComponent, Guid)
		RTTI_DECLARE(ModelComponent)
	};
}