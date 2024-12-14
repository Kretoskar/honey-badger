#pragma once

#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	struct ModelData
	{
		std::string _guid;
		std::vector<std::string> _meshesGuids;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ModelData, _guid, _meshesGuids)
	};
}