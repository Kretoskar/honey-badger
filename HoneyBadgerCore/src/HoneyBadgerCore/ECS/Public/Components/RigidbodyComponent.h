#pragma once

#include <string>
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	struct RigidbodyComponent
	{
		Vec3 Velocity;
		Vec3 Force;
		float Mass;
		float Bounciness;

		std::vector<Vec3> Forces;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(RigidbodyComponent, Velocity, Force, Mass, Bounciness)
		RTTI_DECLARE(RigidbodyComponent)
	};
}