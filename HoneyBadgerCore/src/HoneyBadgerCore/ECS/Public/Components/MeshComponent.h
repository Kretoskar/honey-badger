#pragma once

#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	struct MeshComponent
	{
		std::string MeshGuid;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MeshComponent, MeshGuid)
	};
}