#pragma once
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	class AssetsRegistry;

	struct Scene
	{
	public:
		Scene(AssetsRegistry* assetsRegistry);

		ECS _sceneEcs;
	};
}