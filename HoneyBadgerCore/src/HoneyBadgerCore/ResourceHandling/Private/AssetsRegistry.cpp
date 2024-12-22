#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/Scene/Public/Scene.h"
#include "HoneyBadgerCore/vendor/filesystem.hpp"
#include "HoneyBadgerCore/Scene/Public/Scene.h"
#include "HoneyBadgerCore/vendor/cgltf.h"
#include <HoneyBadgerCore/ResourceHandling/Public/GLTFReader.h>
#include "HoneyBadgerCore/Rendering/Public/Mesh/Model.h"
#include "HoneyBadgerCore/Rendering/Public/Texture.h"

namespace fs = ghc::filesystem;

namespace HoneyBadger
{
	AssetsRegistry* AssetsRegistry::Instance = nullptr;

	void AssetsRegistry::StringToFileQuick(const std::string& s)
	{
		std::ofstream out("output.txt");
		out << s;
	}

	void AssetsRegistry::LoadGltfModel(const std::string& path, HBString name)
	{
		cgltf_data* data = HoneyBadger::GLTFReader::Read(path.c_str());
		if (data)
		{
			std::vector<MeshData> mds = HoneyBadger::GLTFReader::LoadMeshes(data);

			ModelData modelData;
			modelData._guid = GenerateGUID();

			for (int32_t i = 0; i < mds.size(); ++i)
			{
				mds[i]._guid = HoneyBadger::GenerateGUID();
				modelData._meshesGuids.push_back(mds[i]._guid);

				std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(mds[i]);

				std::string nameIndexed = name.Get();
				nameIndexed += std::to_string(i);

				GuidMeshMap.emplace(mds[i]._guid, mesh);
				NameMeshMap.emplace(nameIndexed, mesh);
				MeshNames.push_back(nameIndexed.c_str());

				nlohmann::json j;
				j = mds[i];

				std::string outPath = "../res/meshes/";
				outPath += nameIndexed;
				outPath += ".hbmesh";
				
				std::ofstream out(outPath);
				out << j.dump();
			}

			nlohmann::json j;
			j = modelData;
			modelData._guid = GenerateGUID();

			std::string outPath = "../res/models/";
			outPath += name.Get();
			outPath += ".hbmodel";

			std::ofstream out(outPath);
			out << j.dump();
		}
	}

	void AssetsRegistry::Init()
	{
		Instance = this;

		//LoadGltfModel("bmw.glb", "car");
		LoadEngineAssets();
	
	}

	void AssetsRegistry::Cleanup()
	{
	}

	void AssetsRegistry::LoadEngineAssets()
	{
		LoadAllAssetsInPath(File::GetPathInRes(""));
	}

	void AssetsRegistry::LoadAllAssetsInPath(HBString path)
	{
		// TODO: rewrite this shitty hack
		for (const auto& entry : fs::recursive_directory_iterator(path.Get()))
		{
			std::string pathStr = entry.path().string();
			std::string extension = File::GetFileExtension(pathStr);

			if (extension == "hbshader")
			{
				std::string name = File::GetFileName(pathStr);
				LoadShader(pathStr, name);
			}
			else if (extension == "hbmaterial")
			{
				std::string name = File::GetFileName(pathStr);

				LoadMaterial(pathStr, name);
			}
			else if (extension == "hbmesh")
			{
				std::string name = File::GetFileName(pathStr);

				LoadMesh(pathStr, name);
			}
			else if (extension == "hbscene")
			{
				std::string name = File::GetFileName(pathStr);

				LoadScene(pathStr, name);
			}
			else if (extension == "hbmodel")
			{
				std::string name = File::GetFileName(pathStr);

				LoadModel(pathStr, name);
			}
			else if (extension == "png")
			{
				std::string name = File::GetFileName(pathStr);

				LoadTexture(pathStr, name);
			}
		}
	}

	std::shared_ptr<Mesh> AssetsRegistry::LoadMesh(HBString path, HBString name)
	{
		File file(path.Get());
		if (file.IsValid())
		{
			nlohmann::json j = nlohmann::json::parse(*file.GetFileContents());
			MeshData meshData = j.template get<MeshData>();

			if (std::shared_ptr<Mesh> loadedMesh = GetMeshByGuid(meshData._guid))
			{
				return loadedMesh;
			}

			std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(meshData);
			GuidMeshMap.emplace(meshData._guid, mesh);
			NameMeshMap.emplace(name, mesh);

			MeshNames.push_back(name.Get());
			GuidNameMeshMap.emplace(meshData._guid, name);
			
			return mesh;
		}

		return nullptr;
	}

	std::shared_ptr<Shader> AssetsRegistry::LoadShader(HBString path, HBString name)
	{
		File file(path.Get());
		if (file.IsValid())
		{
			nlohmann::json j = nlohmann::json::parse(*file.GetFileContents());
			ShaderData shaderData = j.template get<ShaderData>();

			if (std::shared_ptr<Shader> loadedShader = GetShaderByGuid(shaderData.Guid))
			{
				return loadedShader;
			}

			std::shared_ptr<Shader> shader = std::make_shared<Shader>(shaderData);
			GuidShaderMap.emplace(shaderData.Guid, shader);
			NameShaderMap.emplace(name, shader);

			return shader;
		}

		return nullptr;
	}

	std::shared_ptr<Material> AssetsRegistry::LoadMaterial(HBString path, HBString name)
	{
		File file(path.Get());
		if (file.IsValid())
		{
			nlohmann::json j = nlohmann::json::parse(*file.GetFileContents());
			MaterialData materialData = j.template get<MaterialData>();

			if (std::shared_ptr<Material> loadedMaterial = GetMaterialByGuid(materialData.Guid))
			{
				return loadedMaterial;
			}

			std::shared_ptr<Material> material = std::make_shared<Material>(materialData);
			GuidMaterialMap.emplace(materialData.Guid, material);
			NameMaterialMap.emplace(name, material);
			MaterialNames.push_back(name.Get());
			NameGuidMaterialMap.emplace(name, materialData.Guid);
			GuidNameMaterialMap.emplace(materialData.Guid, name);

			return material;
		}

		return nullptr;
	}

	std::shared_ptr<Scene> AssetsRegistry::LoadScene(HBString path, HBString name)
	{
		File file(path.Get());
		if (file.IsValid())
		{
			nlohmann::json j = nlohmann::json::parse(*file.GetFileContents());
			SceneData sceneData = j.template get<SceneData>();

			if (std::shared_ptr<Scene> loadedScene = GetSceneByGuid(sceneData.Guid))
			{
				return loadedScene;
			}

			std::shared_ptr<Scene> scene = std::make_shared<Scene>(sceneData);
			GuidSceneMap.emplace(sceneData.Guid, scene);
			NameSceneMap.emplace(name, scene);

			return scene;
		}

		return nullptr;
	}

	std::shared_ptr<ModelData> AssetsRegistry::LoadModel(HBString path, HBString name)
	{
		File file(path.Get());
		if (file.IsValid())
		{
			nlohmann::json j = nlohmann::json::parse(*file.GetFileContents());
			ModelData modelData = j.template get<ModelData>();

			if (std::shared_ptr<ModelData> loadedModel = GetModelByGuid(modelData._guid))
			{
				return loadedModel;
			}

			std::shared_ptr<ModelData> model = std::make_shared<ModelData>(modelData);
			GuidModelMap.emplace(modelData._guid, model);
			NameModelMap.emplace(name, model);
			ModelNames.push_back(name.Get());

			return model;
		}

		return nullptr;
	}

	std::shared_ptr<Texture> AssetsRegistry::LoadTexture(HBString path, HBString name)
	{
		if (std::shared_ptr<Texture> loadedTex = GetTextureByName(name))
		{
			return loadedTex;
		}

		std::shared_ptr<Texture> tex = std::make_shared<Texture>(path, GL_TEXTURE0, GL_RGB);
		GuidTextureMap.emplace(GenerateGUID(), tex);
		NameTextureMap.emplace(name, tex);
		return tex;
	}

	std::shared_ptr<Mesh> AssetsRegistry::GetMeshByName(HBString name)
	{
		if (NameMeshMap.find(name) != NameMeshMap.end())
		{
			return NameMeshMap[name];
		}

		return nullptr;
	}

	std::shared_ptr<Mesh> AssetsRegistry::GetMeshByGuid(HBString guid)
	{
		if (GuidMeshMap.find(guid) != GuidMeshMap.end())
		{
			return GuidMeshMap[guid];
		}

		return nullptr;
	}

	std::shared_ptr<Shader> AssetsRegistry::GetShaderByName(HBString name)
	{
		if (NameShaderMap.find(name) != NameShaderMap.end())
		{
			return NameShaderMap[name];
		}

		return nullptr;
	}
	std::shared_ptr<Shader> AssetsRegistry::GetShaderByGuid(HBString guid)
	{
		if (GuidShaderMap.find(guid) != GuidShaderMap.end())
		{
			return GuidShaderMap[guid];
		}

		return nullptr;
	}
	std::shared_ptr<Material> AssetsRegistry::GetMaterialByName(HBString name)
	{
		if (NameMaterialMap.find(name) != NameMaterialMap.end())
		{
			return NameMaterialMap[name];
		}

		return nullptr;
	}

	std::shared_ptr<Material> AssetsRegistry::GetMaterialByGuid(HBString guid)
	{
		if (GuidMaterialMap.find(guid) != GuidMaterialMap.end())
		{
			return GuidMaterialMap[guid];
		}

		return nullptr;
	}

	std::shared_ptr<Scene> AssetsRegistry::GetSceneByName(HBString name)
	{
		if (NameSceneMap.find(name) != NameSceneMap.end())
		{
			return NameSceneMap[name];
		}

		return nullptr;
	}

	std::shared_ptr<Scene> AssetsRegistry::GetSceneByGuid(HBString guid)
	{
		if (GuidSceneMap.find(guid) != GuidSceneMap.end())
		{
			return GuidSceneMap[guid];
		}

		return nullptr;
	}

	std::shared_ptr<ModelData> AssetsRegistry::GetModelByName(HBString name)
	{
		if (NameModelMap.find(name) != NameModelMap.end())
		{
			return NameModelMap[name];
		}

		return nullptr;
	}

	std::shared_ptr<ModelData> AssetsRegistry::GetModelByGuid(HBString guid)
	{
		if (GuidModelMap.find(guid) != GuidModelMap.end())
		{
			return GuidModelMap[guid];
		}

		return nullptr;
	}
	
	std::shared_ptr<Texture> AssetsRegistry::GetTextureByName(HBString name)
	{
		if (NameTextureMap.find(name) != NameTextureMap.end())
		{
			return NameTextureMap[name];
		}

		return nullptr;
	}

	std::shared_ptr<Texture> AssetsRegistry::GetTextureByGuid(HBString guid)
	{
		if (GuidTextureMap.find(guid) != GuidTextureMap.end())
		{
			return GuidTextureMap[guid];
		}

		return nullptr;
	}

	HBString AssetsRegistry::GetMeshName(HBString guid)
	{
		if (GuidNameMeshMap.find(guid) != GuidNameMeshMap.end())
		{
			return GuidNameMeshMap[guid];
		}

		return "";
	}
	HBString AssetsRegistry::GetMaterialGuid(HBString name)
	{
		if (NameGuidMaterialMap.find(name) != NameGuidMaterialMap.end())
		{
			return NameGuidMaterialMap[name];
		}

		return "";
	}
	HBString AssetsRegistry::GetMaterialName(HBString guid)
	{
		if (GuidNameMaterialMap.find(guid) != GuidNameMaterialMap.end())
		{
			return GuidNameMaterialMap[guid];
		}

		return "";
	}
}