#pragma once

#include <set>

#include "HoneyBadgerCore/ECS/Public/ECSTypes.h"

namespace HoneyBadger
{
	class ECS;

	class System
	{
	public:

		Signature _sig{};
		std::set<Entity> _entities{};
		ECS* _ecs;
	};
}