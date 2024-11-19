#pragma once

#include <string>
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"

namespace HoneyBadger
{
	class Asset
	{
		Asset()
			: _guid(std::move(GenerateGUID())) {}

		virtual AssetType GetAssetType() { return AssetType::Invalid; };

	private:
		std::string _guid;
	};
}