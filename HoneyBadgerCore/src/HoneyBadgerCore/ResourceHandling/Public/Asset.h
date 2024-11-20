#pragma once

#include <string>
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

namespace HoneyBadger
{
	class Asset
	{
	public:
		Asset()
			: _guid(std::move(GenerateGUID())) {}

		virtual AssetType GetAssetType() { return AssetType::Invalid; };

		std::string Serialize();
		void Load(File* file);

	private:
		std::string _guid;
	};
}