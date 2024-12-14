#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Components/Components.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/ModelComponent.h"
#include "HoneyBadgerCore/Core/Public/RTTI.h"

namespace HoneyBadger
{
	std::vector<char*> Components::Names = {};

	std::unordered_map<HBString, std::function<void(ECS&, Entity)>, HBString::HBStringHasher> Components::ComponentsAddMap = {};
	std::unordered_map<HBString, HBString, HBString::HBStringHasher> Components::ComponentsNameTypeIdNameMap = {};

#define DRAW_COMPONENT(_TClass) \
if (HoneyBadger::_TClass* comp = ecs.GetComponentPtr<_TClass>(e)) \
{ \
	comp->DrawProperties(); \
} \

#define REGISTER_COMPONENT(_TClass) \
ecs.RegisterComponent<HoneyBadger::_TClass>(); \
Components::ComponentsAddMap.insert(std::make_pair \
	<HBString, std::function<void(ECS&, Entity)>> \
		(#_TClass, &Components::AddComponent<_TClass>)); \
Names.push_back(#_TClass); \
Components::ComponentsNameTypeIdNameMap.insert(std::make_pair<HBString, HBString>(#_TClass, typeid(_TClass).name()));


#define ADD_COMPONENT(_TClass) \
if (name == QUOTE(_TClass)) \
{ \
	AddComponent<_TClass>(ECS, e); \
}

	void HoneyBadger::Components::DrawAllComponents(ECS& ecs,  Entity e)
	{
		
		DRAW_COMPONENT(NameComponent)
		DRAW_COMPONENT(TransformComponent)
		DRAW_COMPONENT(MeshComponent)
		DRAW_COMPONENT(ModelComponent)
	}

	void HoneyBadger::Components::RegisterAllComponents(ECS& ecs)
	{
		REGISTER_COMPONENT(TransformComponent)
		REGISTER_COMPONENT(MeshComponent)
		REGISTER_COMPONENT(NameComponent)
		REGISTER_COMPONENT(ModelComponent)
	}

	void Components::AddComponent(const char* name, ECS& ECS, Entity e)
	{
		ADD_COMPONENT(TransformComponent)
		ADD_COMPONENT(MeshComponent)
		ADD_COMPONENT(NameComponent)
		ADD_COMPONENT(ModelComponent)
	}

#undef DRAW_COMPONENT
#undef REGISTER_COMPONENT
}
