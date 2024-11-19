#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Asset.h"
#include <HoneyBadgerCore/Core/Public/HBString.h>

namespace HoneyBadger
{
	nlohmann::json Asset::Serialize()
	{
		nlohmann::json retJson;

		retJson["Guid"] = _guid;

		switch (GetAssetType())
		{
		case AssetType::Mesh:
			retJson["AssetType"] = "Mesh";
			break;
		case AssetType::Material:
			retJson["AssetType"] = "Material";
			break;

		default:
			retJson["AssetType"] = "Invalid";
			break;
		}

		return retJson;
	}

	bool Asset::Deserialize(const std::string& content)
	{
		nlohmann::json assetJson = nlohmann::json::parse(content);

		_guid = assetJson["Guid"];
		std::string assetType = assetJson["AssetType"];

		if (assetType == "Mesh")
		{
			_assetType = AssetType::Mesh;
		}
		else if (assetType == "Material")
		{
			_assetType = AssetType::Material;
		}
		else
		{
			_assetType = AssetType::Invalid;
		}

		return Deserialize_Internal(assetJson);
	}

	bool Asset::Deserialize_Internal(nlohmann::json assetJson)
	{
		return false;
	}
}