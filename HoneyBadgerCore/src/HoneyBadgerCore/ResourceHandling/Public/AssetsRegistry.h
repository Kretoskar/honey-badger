#pragma once

#include <memory>
#include <string>

namespace HoneyBadger
{
	enum class AssetType
	{
		Invalid,
		Mesh,
		Material
	};

	struct Material;
	class Shader;
	class Mesh;

	class AssetsRegistry
	{
	public:
		AssetsRegistry() {}

		void Init();
		void Cleanup();

		std::shared_ptr<Shader> UnlitColorShader;
		std::shared_ptr<Material> UnlitColorMaterial;
		std::shared_ptr<Mesh> Plane;
	};
}