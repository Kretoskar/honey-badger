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
	void AssetsRegistry::Init()
	{
		LoadShader("shaders/unlit_color.hbshader", "unlit_color");

		UnlitColorMaterial = std::make_shared<Material>(nullptr, nullptr, *GetShaderByName("unlit_color"));

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

			std::shared_ptr<Shader> shader = std::make_shared<Shader>(shaderData);
			GuidShaderMap.emplace(shaderData.Guid, shader);
			NameShaderMap.emplace(name, shader);

			return shader;
		}

		return nullptr;
	}

	std::shared_ptr<Mesh> AssetsRegistry::GetMeshByName(HBString name)
	{
		if (NameMeshMap.find(name) != NameMeshMap.end())
		{
			return NameMeshMap[name];
		}

		return std::shared_ptr<Mesh>();
	}

	std::shared_ptr<Shader> AssetsRegistry::GetShaderByName(HBString name)
	{
		if (NameShaderMap.find(name) != NameShaderMap.end())
		{
			return NameShaderMap[name];
		}

		return std::shared_ptr<Shader>();
	}
}