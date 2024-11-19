#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Asset.h"

namespace HoneyBadger
{
	std::string Asset::Serialize()
	{
		std::string result;
		result.append("[guid]: " + _guid + '\n');

		switch (GetAssetType())
		{
		case AssetType::Mesh:
			result.append("[type]: Mesh\n");
			break;
		case AssetType::Material:
			result.append("[type]: Material\n");
			break;

		default:
			result.append("[type]: Invalid\n");
			break;
		}

		return result;
	}

	void Asset::Load(File* file)
	{
		if (!file)
		{
			return;
		}

		const std::vector<std::string>& lines = file->GetLines();
	}
}