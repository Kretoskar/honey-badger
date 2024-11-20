#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMeshes/PlaneMesh.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

#include "HoneyBadgerCore/vendor/json.hpp"

void HoneyBadger::AssetsRegistry::Init()
{
	UnlitColorShader = std::make_shared<Shader>("Shaders/Debug.frag", "Shaders/pbr.vert");
	UnlitColorShader->Bind();

	UnlitColorMaterial = std::make_shared<Material>(nullptr, nullptr, *UnlitColorShader.get());
	UnlitColorMaterial->Bind();

	Plane = std::make_shared<PlaneMesh>(Vec3(0.0f,1.0f, 1.0f));

	Mesh* planeMesh = static_cast<Mesh*>(Plane.get());

	nlohmann::json j = *planeMesh;

	std::string jS = j.dump(4);
	std::cout << jS;

	
}

void HoneyBadger::AssetsRegistry::Cleanup()
{
}
