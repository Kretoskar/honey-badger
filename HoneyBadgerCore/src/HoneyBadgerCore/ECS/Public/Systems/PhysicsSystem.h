#pragma once

#include "HoneyBadgerCore/ECS/Public/System.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	class PhysicsSystem : public System
	{
	public:
		void Register(ECS& ecs);
		void Update(float deltaTime);
	};
}