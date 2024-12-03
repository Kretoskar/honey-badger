#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"

namespace HoneyBadger
{
	RTTI_BEGIN(NameComponent)
	RTTI_PROPERTY_EDITABLE(name, Name)
	RTTI_END()
}