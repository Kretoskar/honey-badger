#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"

void HoneyBadger::AssetsRegistry::Init()
{
	UnlitColorShader = std::make_shared<Shader>("Shaders/unlit_color.frag", "Shaders/Debug.vert");
	UnlitColorShader->Bind();

	UnlitColorMaterial = std::make_shared<Material>(nullptr, nullptr, *UnlitColorShader.get());
	UnlitColorMaterial->Bind();
}

void HoneyBadger::AssetsRegistry::Cleanup()
{
}
