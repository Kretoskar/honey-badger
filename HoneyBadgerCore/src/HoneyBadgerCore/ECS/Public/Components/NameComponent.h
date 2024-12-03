#pragma once

#include <string>
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	struct NameComponent
	{
		std::string Name;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(NameComponent, Name)
		RTTI_DECLARE(NameComponent)
	};
}