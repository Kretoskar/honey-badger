#pragma once

#include "HoneyBadgerCore/Core/Public/RTTI.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	struct MeshComponent
	{
		std::string MeshGuid;

		int32_t GetVerts();

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MeshComponent, MeshGuid)
		RTTI_DECLARE(MeshComponent)
	};
}