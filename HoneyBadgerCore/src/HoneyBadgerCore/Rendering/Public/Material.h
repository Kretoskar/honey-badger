#pragma once

namespace HoneyBadger
{
	class Shader;
	class Texture;

	struct Material
	{
		Material() = default;
		Material(Texture* InDiffuseMap, Texture* InSpecularMap, Shader& InShader);
		void Bind();

		Texture* DiffuseMap;
		Texture* SpecularMap;
		Shader* Shader;
	};
}