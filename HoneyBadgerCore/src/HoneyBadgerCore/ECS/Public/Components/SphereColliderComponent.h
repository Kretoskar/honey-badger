#pragma once

#include <string>
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	struct SphereColliderComponent
	{
		float Radius;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SphereColliderComponent, Radius)
		RTTI_DECLARE(SphereColliderComponent)
	};
}