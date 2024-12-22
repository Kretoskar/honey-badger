#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/DirectionalLightComponent.h"

namespace HoneyBadger
{
	RTTI_BEGIN(DirectionalLightComponent)
	RTTI_PROPERTY_EDITABLE(Intensity, Intensity)
	RTTI_PROPERTY_EDITABLE(AmbientIntensity, AmbientIntensity)
	RTTI_PROPERTY_EDITABLE(Color, LightColor)
	RTTI_END()
}