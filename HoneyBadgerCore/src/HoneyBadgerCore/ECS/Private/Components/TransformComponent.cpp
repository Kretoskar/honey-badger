#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/UI/Public/PropertyDrawer.h"

namespace HoneyBadger
{
	RTTI_BEGIN(TransformComponent)
	RTTI_PROPERTY_EDITABLE(pos, Position)
	RTTI_PROPERTY_EDITABLE(rot, Rotation)
	RTTI_PROPERTY_EDITABLE(scale, Scale)
	RTTI_END()
}