#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Texture.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"

namespace HoneyBadger
{
	Material::Material(const MaterialData& matData)
		: materialData(matData)
	{
		//if (DiffuseMap)
		//{
		//	Shader->AssignDiffuseMap(*DiffuseMap);
		//}
		//
		//if (SpecularMap)
		//{
		//	Shader->AssignSpecularMap(*SpecularMap);
		//}

		shader = AssetsRegistry::Instance->GetShaderByGuid(matData.ShaderGuid);
	}

	void Material::Bind()
	{
		if (shader)
		{
			shader->Bind();
		}

		//if (DiffuseMap)
		//{
		//	DiffuseMap->Bind();
		//}
		//
		//if (SpecularMap)
		//{
		//	SpecularMap->Bind();
		//}
	}
}