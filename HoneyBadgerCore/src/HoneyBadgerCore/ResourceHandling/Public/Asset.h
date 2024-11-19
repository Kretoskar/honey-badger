#pragma once

#include <string>
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	class Asset
	{
	public:
		Asset()
			: _guid(std::move(GenerateGUID())) {}

		AssetType GetAssetType() { return _assetType; };

		nlohmann::json Serialize();
		bool Deserialize(const std::string& content);

	protected:
		virtual bool Deserialize_Internal(nlohmann::json assetJson);

		std::string _guid;
		AssetType _assetType = AssetType::Invalid;
	};
}