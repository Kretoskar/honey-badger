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
		std::string DiffuseMapName;
		std::string SpecularMapName;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MaterialData, Guid, ShaderGuid, DiffuseMapName, SpecularMapName)
	};

	struct Material
	{
		Material(const MaterialData& matData)
			: _materialData(matData) {}
		void Bind();

		std::shared_ptr<Shader> GetShader();
		const std::string& GetDiffuseMapName() { return _materialData.DiffuseMapName; }

	private:
		MaterialData _materialData;
		std::shared_ptr<Shader> _shader;
	};
}