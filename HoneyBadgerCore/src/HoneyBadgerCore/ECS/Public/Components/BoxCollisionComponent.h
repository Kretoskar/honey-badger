#pragma once

#include <string>
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	struct BoxCollisionComponent
	{
		std::string Name;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(BoxCollisionComponent, Name)
		RTTI_DECLARE(BoxCollisionComponent)
	};
}