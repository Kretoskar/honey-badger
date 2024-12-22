#include "hbpch.h"
#include "HoneyBadgerCore/ECS/Public/Systems/LightingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/DirectionalLightComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Math/Public/Vec4.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"

namespace HoneyBadger
{
	void LightRenderingSystem::Register(ECS& ecs, Camera* camera)
	{
		_camera = camera;

		REGISTER_SYSTEM()
		REGISTER_COMPONENT_IN_SYSTEM(DirectionalLightComponent)
		REGISTER_COMPONENT_IN_SYSTEM(TransformComponent)
			
	}

	void LightRenderingSystem::UpdateShaders()
	{
		for (Entity entity : _entities)
		{
			TransformComponent& transfComp = _ecs->GetComponent<TransformComponent>(entity);
			Vec4 dir = transfComp.ToRotMat4().forward;
			
			DirectionalLightComponent& lightComp = _ecs->GetComponent<DirectionalLightComponent>(entity);

			for (auto& shaderPair : AssetsRegistry::Instance->GuidShaderMap)
			{
				auto shader = shaderPair.second;
				shader->SetLightColor(Vec4(lightComp.LightColor.x, lightComp.LightColor.y, lightComp.LightColor.z, 1.0f));
				shader->SetLightDirection(Vec3(dir.x, dir.y, dir.z));
				shader->SetCameraPosition(_camera->GetPosition());
			}
		}
	}
}