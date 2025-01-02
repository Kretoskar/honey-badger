#pragma once

#include <memory>
#include "HoneyBadgerCore/Rendering/Public/Shader.h"

namespace HoneyBadger
{
	class Camera;

	class Skybox
	{
	public:
		void Init(Camera* cam);
		void Render();

	private:
		uint32_t _tex;

		std::shared_ptr<Shader> shader;
		Camera* camera;
		uint32_t skyboxVAO, skyboxVBO, skyboxEBO;
	};
}