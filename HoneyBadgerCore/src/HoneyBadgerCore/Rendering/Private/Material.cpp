#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Texture.h"

namespace HoneyBadger
{
	Material::Material(Texture* InDiffuseMap, Texture* InSpecularMap, HoneyBadger::Shader& InShader)
		: DiffuseMap(InDiffuseMap), SpecularMap(InSpecularMap), Shader(&InShader)
	{
		if (DiffuseMap)
		{
			Shader->AssignDiffuseMap(*DiffuseMap);
		}

		if (SpecularMap)
		{
			Shader->AssignSpecularMap(*SpecularMap);
		}
	}

	void Material::Bind()
	{
		if (Shader)
		{
			Shader->Bind();
		}

		if (DiffuseMap)
		{
			DiffuseMap->Bind();
		}

		if (SpecularMap)
		{
			SpecularMap->Bind();
		}
	}
}