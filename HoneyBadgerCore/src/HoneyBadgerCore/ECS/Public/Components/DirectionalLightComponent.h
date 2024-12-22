#pragma once

#include <string>
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	struct DirectionalLightComponent
	{
		float Intensity = 1.0f;
		float AmbientIntensity = 0.2f;
		Vec3 LightColor = { 1.0f, 1.0f, 1.0f };

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(DirectionalLightComponent, Intensity, AmbientIntensity, LightColor)
		RTTI_DECLARE(DirectionalLightComponent)
	};
}