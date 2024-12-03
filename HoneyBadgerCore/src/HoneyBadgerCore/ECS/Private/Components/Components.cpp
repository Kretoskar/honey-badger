#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/Components.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
#define DRAW_COMPONENT(_TClass) \
if (HoneyBadger::_TClass* comp = ecs.GetComponentPtr<_TClass>(e)) \
{ \
	comp->DrawProperties(); \
} \

	void Components::DrawAllComponents(ECS& ecs,  Entity e)
	{
		DRAW_COMPONENT(NameComponent)
		DRAW_COMPONENT(TransformComponent)
		DRAW_COMPONENT(MeshComponent)
	}

#undef DRAW_COMPONENT
}
