#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Texture.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Core/Public/Logger.h"

namespace HoneyBadger
{
	void Material::Bind()
	{
		std::shared_ptr<Shader> shader = GetShader();
		if (shader)
		{
			shader->Bind();
		}
		else
		{
			HB_LOG_ERROR("Trying to bind material %s with null shader %s", _materialData.Guid, _materialData.ShaderGuid)
		}
	}

	std::shared_ptr<Shader> Material::GetShader()
	{
		if (!_shader)
		{
			_shader = AssetsRegistry::Instance->GetShaderByGuid(_materialData.ShaderGuid);
		}
		return _shader;
	}
}