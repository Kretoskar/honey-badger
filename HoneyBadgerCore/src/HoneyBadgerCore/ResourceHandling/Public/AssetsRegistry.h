#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadger
{
	enum class AssetType
	{
		Invalid,
		Mesh,
		Material
	};

	struct Material;
	class Shader;
	class Mesh;

	class AssetsRegistry
	{
	public:
		AssetsRegistry() {}

		void Init();
		void Cleanup();
		void LoadEngineAssets();
		void LoadAllAssetsInPath(HBString path);

		std::shared_ptr<Mesh> LoadMesh(HBString path, HBString name);
		std::shared_ptr<Shader> LoadShader(HBString path, HBString name);
		std::shared_ptr<Material> LoadMaterial(HBString path, HBString name);

		std::shared_ptr<Mesh> GetMeshByName(HBString name);
		std::shared_ptr<Mesh> GetMeshByGuid(HBString guid);
		std::shared_ptr<Shader> GetShaderByName(HBString name);
		std::shared_ptr<Shader> GetShaderByGuid(HBString guid);
		std::shared_ptr<Material> GetMaterialByName(HBString name);
		std::shared_ptr<Material> GetMaterialByGuid(HBString guid);

		std::unordered_map<HBString, std::shared_ptr<Shader>, HBString::HBStringHasher> GuidShaderMap;
		std::unordered_map<HBString, std::shared_ptr<Shader>, HBString::HBStringHasher> NameShaderMap;

		std::unordered_map<HBString, std::shared_ptr<Material>, HBString::HBStringHasher> GuidMaterialMap;
		std::unordered_map<HBString, std::shared_ptr<Material>, HBString::HBStringHasher> NameMaterialMap;

		std::unordered_map<HBString, std::shared_ptr<Mesh>, HBString::HBStringHasher> GuidMeshMap;
		std::unordered_map<HBString, std::shared_ptr<Mesh>, HBString::HBStringHasher> NameMeshMap;

		static AssetsRegistry* Instance;
	};
}