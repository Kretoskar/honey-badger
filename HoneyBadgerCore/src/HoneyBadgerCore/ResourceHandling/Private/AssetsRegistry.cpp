#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

void HoneyBadger::AssetsRegistry::Init()
{
	UnlitColorShader = std::make_shared<Shader>("Shaders/unlit_color.frag", "Shaders/Debug.vert");
	UnlitColorShader->Bind();

	UnlitColorMaterial = std::make_shared<Material>(nullptr, nullptr, *UnlitColorShader.get());
	UnlitColorMaterial->Bind();

	Plane = std::make_shared<PlaneMesh>(Vec3(.1f,0.0f, 0.0f));
}

void HoneyBadger::AssetsRegistry::Cleanup()
{
}
