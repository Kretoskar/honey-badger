#pragma once

#include <string>
#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	struct NameComponent
	{
		std::string Name;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(NameComponent, Name)
	};
}