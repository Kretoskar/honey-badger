#pragma once

#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/System.h"

namespace HoneyBadger
{
	class Camera;

	class RenderingSystem : public System
	{
	public:
		void Init(Camera* camera);
		void Render();

	private:
		Camera* _camera;
	};
}