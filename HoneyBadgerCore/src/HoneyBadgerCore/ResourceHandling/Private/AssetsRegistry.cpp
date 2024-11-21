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
	UnlitColorShader = Shader::LoadShader("shaders/unlit_color.hbshader");
	UnlitColorShader->Bind();

	UnlitColorMaterial = std::make_shared<Material>(nullptr, nullptr, *UnlitColorShader.get());
	UnlitColorMaterial->Bind();

	Plane = Mesh::LoadMesh("meshes/Plane.hbmesh");
}

void HoneyBadger::AssetsRegistry::Cleanup()
{
}
