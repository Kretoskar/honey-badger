#pragma once

#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	class Shader;
	class Texture;

	struct MaterialData
	{
		std::string Guid;
		std::string ShaderGuid;
		std::string DiffuseMapGuid;
		std::string SpecularMapGuid;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MaterialData, Guid, ShaderGuid, DiffuseMapGuid, SpecularMapGuid)
	};

	struct Material
	{
		Material(const MaterialData& matData);
		void Bind();

		MaterialData materialData;
		std::shared_ptr<Shader> shader;
	};
}