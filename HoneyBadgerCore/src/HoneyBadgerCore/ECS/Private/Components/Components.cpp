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
} 

#define REGISTER_COMPONENT(_TClass) \
ecs.RegisterComponent<HoneyBadger::_TClass>();

	void Components::DrawAllComponents(ECS& ecs,  Entity e)
	{
		DRAW_COMPONENT(NameComponent)
		DRAW_COMPONENT(TransformComponent)
		DRAW_COMPONENT(MeshComponent)
	}

	void Components::RegisterAllComponents(ECS& ecs)
	{
		REGISTER_COMPONENT(TransformComponent)
		REGISTER_COMPONENT(MeshComponent)
		REGISTER_COMPONENT(NameComponent)
	}

#undef DRAW_COMPONENT
#undef REGISTER_COMPONENT
}
