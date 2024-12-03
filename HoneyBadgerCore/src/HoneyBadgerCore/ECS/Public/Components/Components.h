#pragma once

#include "HoneyBadgerCore/ECS/Public/ECSTypes.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	class Components
	{
	public:
		static void DrawAllComponents(ECS& ECS, Entity e);
		static void RegisterAllComponents(ECS& ecs);
	};
}