#pragma once

#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/ECSTypes.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadger
{
	class Components
	{
	public:
		static void DrawAllComponents(ECS& ECS, Entity e);
		static void RegisterAllComponents(ECS& ecs);
		static std::vector<char*> Names;

		static void AddComponent(const char* name, ECS& ECS, Entity e);

		template <typename T>
		static void AddComponent(ECS& ECS, Entity e);

		static std::unordered_map<HBString, std::function<void(ECS&, Entity)>, HBString::HBStringHasher> ComponentsAddMap;
		static std::unordered_map<HBString, HBString, HBString::HBStringHasher> ComponentsNameTypeIdNameMap;
	};

	template<typename T>
	void Components::AddComponent(ECS& ECS, Entity e)
	{
		if (!ECS.GetComponentPtr<T>(e))
		{
			ECS.AddComponent<T>(e);
		}
	}
}