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

		std::shared_ptr<Mesh> LoadMesh(HBString path, HBString name);

		std::shared_ptr<Mesh> GetMeshByName(HBString name);

		std::unordered_map<HBString, std::shared_ptr<Shader>, HBString::HBStringHasher> GuidShaderMap;
		std::unordered_map<HBString, std::shared_ptr<Shader>, HBString::HBStringHasher> NameShaderMap;

		std::unordered_map<HBString, std::shared_ptr<Material>, HBString::HBStringHasher> GuidMaterialMap;
		std::unordered_map<HBString, std::shared_ptr<Material>, HBString::HBStringHasher> NameMaterialMap;

		std::unordered_map<HBString, std::shared_ptr<Mesh>, HBString::HBStringHasher> GuidMeshMap;
		std::unordered_map<HBString, std::shared_ptr<Mesh>, HBString::HBStringHasher> NameMeshMap;

		std::shared_ptr<Shader> UnlitColorShader;
		std::shared_ptr<Material> UnlitColorMaterial;
	};
}