#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadger
{
	struct ModelData;

	enum class AssetType
	{
		Invalid,
		Mesh,
		Material
	};

	struct Material;
	class Shader;
	class Mesh;
	class Scene;
	class Texture;

	class AssetsRegistry
	{
	public:
		AssetsRegistry() {}

		void Init();
		void Cleanup();
		void LoadEngineAssets();
		void LoadAllAssetsInPath(HBString path);

		static void StringToFileQuick(const std::string& s);
		void LoadGltfModel (const std::string& path, HBString name);

		std::shared_ptr<Mesh> LoadMesh(HBString path, HBString name);
		std::shared_ptr<Shader> LoadShader(HBString path, HBString name);
		std::shared_ptr<Material> LoadMaterial(HBString path, HBString name);
		std::shared_ptr<Scene> LoadScene(HBString path, HBString name);
		std::shared_ptr<ModelData> LoadModel(HBString path, HBString name);
		std::shared_ptr<Texture> LoadTexture(HBString path, HBString name);

		std::shared_ptr<Mesh> GetMeshByName(HBString name);
		std::shared_ptr<Mesh> GetMeshByGuid(HBString guid);
		std::shared_ptr<Shader> GetShaderByName(HBString name);
		std::shared_ptr<Shader> GetShaderByGuid(HBString guid);
		std::shared_ptr<Material> GetMaterialByName(HBString name);
		std::shared_ptr<Material> GetMaterialByGuid(HBString guid);
		std::shared_ptr<Scene> GetSceneByName(HBString name);
		std::shared_ptr<Scene> GetSceneByGuid(HBString guid);
		std::shared_ptr<ModelData> GetModelByName(HBString name);
		std::shared_ptr<ModelData> GetModelByGuid(HBString guid);
		std::shared_ptr<Texture> GetTextureByName(HBString name);
		std::shared_ptr<Texture> GetTextureByGuid(HBString guid);

		HBString GetMeshName(HBString guid);
		HBString GetMaterialGuid(HBString name);
		HBString GetMaterialName(HBString guid);

		std::unordered_map<HBString, std::shared_ptr<Shader>, HBString::HBStringHasher> GuidShaderMap;
		std::unordered_map<HBString, std::shared_ptr<Shader>, HBString::HBStringHasher> NameShaderMap;

		std::unordered_map<HBString, std::shared_ptr<Material>, HBString::HBStringHasher> GuidMaterialMap;
		std::unordered_map<HBString, std::shared_ptr<Material>, HBString::HBStringHasher> NameMaterialMap;
		std::unordered_map<HBString, HBString, HBString::HBStringHasher> NameGuidMaterialMap;
		std::unordered_map<HBString, HBString, HBString::HBStringHasher> GuidNameMaterialMap;
		std::vector<std::string> MaterialNames;

		std::unordered_map<HBString, std::shared_ptr<Mesh>, HBString::HBStringHasher> GuidMeshMap;
		std::unordered_map<HBString, std::shared_ptr<Mesh>, HBString::HBStringHasher> NameMeshMap;
		std::unordered_map<HBString, HBString, HBString::HBStringHasher> GuidNameMeshMap;
		std::vector<std::string> MeshNames;

		std::unordered_map<HBString, std::shared_ptr<Scene>, HBString::HBStringHasher> GuidSceneMap;
		std::unordered_map<HBString, std::shared_ptr<Scene>, HBString::HBStringHasher> NameSceneMap;

		std::unordered_map<HBString, std::shared_ptr<ModelData>, HBString::HBStringHasher> GuidModelMap;
		std::unordered_map<HBString, std::shared_ptr<ModelData>, HBString::HBStringHasher> NameModelMap;
		std::vector<std::string> ModelNames;

		std::unordered_map<HBString, std::shared_ptr<Texture>, HBString::HBStringHasher> GuidTextureMap;
		std::unordered_map<HBString, std::shared_ptr<Texture>, HBString::HBStringHasher> NameTextureMap;

		static AssetsRegistry* Instance;
	};
}