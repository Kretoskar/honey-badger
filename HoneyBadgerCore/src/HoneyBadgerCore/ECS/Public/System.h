#pragma once

#include <set>

#include "HoneyBadgerCore/ECS/Public/ECSTypes.h"

namespace HoneyBadger
{
#define REGISTER_SYSTEM() ecs.RegisterSystem(this);
#define REGISTER_COMPONENT_IN_SYSTEM(_TClass) ecs.RegisterComponentInSystem<HoneyBadger::_TClass>(*this);

	class ECS;

	class System
	{
	public:

		Signature _sig{};
		std::set<Entity> _entities{};
		ECS* _ecs;
	};
}