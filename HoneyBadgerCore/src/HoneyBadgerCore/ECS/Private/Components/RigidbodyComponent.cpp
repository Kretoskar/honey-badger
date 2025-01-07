#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/RigidbodyComponent.h"

namespace HoneyBadger
{
	RTTI_BEGIN(RigidbodyComponent)
	RTTI_PROPERTY_EDITABLE(Velocity, Velocity)
	RTTI_PROPERTY_EDITABLE(Force, Force)
	RTTI_PROPERTY_EDITABLE(Mass, Mass)
	RTTI_PROPERTY_EDITABLE(Bounciness, Bounciness)
	RTTI_END()
}