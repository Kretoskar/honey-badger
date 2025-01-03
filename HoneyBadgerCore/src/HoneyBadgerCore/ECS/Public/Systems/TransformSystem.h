#pragma once

#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	class TransformSystem : public System
	{
	public:
		void Register(ECS& ecs);
		void UpdateWorldTransforms();
	};
}