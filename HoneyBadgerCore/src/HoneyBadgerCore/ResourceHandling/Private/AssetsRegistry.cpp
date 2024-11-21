#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	AssetsRegistry* AssetsRegistry::Instance = nullptr;

	void StringToFileQuick(const std::string& s)
	{
		std::ofstream out("output.txt");
		out << s;
	}

	void AssetsRegistry::Init()
	{
		Instance = this;

		LoadShader("shaders/unlit_color.hbshader", "unlit_color");
		LoadMaterial("materials/unlit_color.hbmaterial", "unlit_color");
		LoadMesh("meshes/Plane.hbmesh", "Plane");
	}

	void AssetsRegistry::Cleanup()
	{
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

			return material;
		}

		return nullptr;
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
}