#pragma once

#include <memory>
#include <string>

namespace HoneyBadger
{
	struct Material;
	class Shader;

	class AssetsRegistry
	{
	public:
		AssetsRegistry() {}

		void Init();
		void Cleanup();

		std::shared_ptr<Shader> UnlitColorShader;
		std::shared_ptr<Material> UnlitColorMaterial;
	};
}