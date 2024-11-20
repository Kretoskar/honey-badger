#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/vendor/json.hpp"

void HoneyBadger::AssetsRegistry::Init()
{
	UnlitColorShader = std::make_shared<Shader>("Shaders/Debug.frag", "Shaders/pbr.vert");
	UnlitColorShader->Bind();

	UnlitColorMaterial = std::make_shared<Material>(nullptr, nullptr, *UnlitColorShader.get());
	UnlitColorMaterial->Bind();

	File file("meshes/Plane.hbmesh");
	nlohmann::json j = nlohmann::json::parse(*file.GetFileContents());

	MeshData meshData = j.template get<MeshData>();

	Plane = std::make_shared<Mesh>(meshData);
}

void HoneyBadger::AssetsRegistry::Cleanup()
{
}
