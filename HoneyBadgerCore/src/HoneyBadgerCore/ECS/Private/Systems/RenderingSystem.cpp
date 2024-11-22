#include "hbpch.h"

#include "HoneyBadgerCore/ECS/Public/Systems/RenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"

#include "HoneyBadgerCore/Math/Public/Mat4.h"

#include "HoneyBadgerCore/Core/Public/Engine.h"

void HoneyBadger::RenderingSystem::Init(Camera* camera)
{
	_camera = camera;
}

void HoneyBadger::RenderingSystem::Render()
{
	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		MeshComponent& meshComp = _ecs->GetComponent<MeshComponent>(entity);

		if (meshComp.Mesh)
		{
			// TODO: take material from component
			Material* mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByName("unlit_color").get();
			
			if (std::shared_ptr<Shader> shader = mat->GetShader())
			{
				shader->SetModelMatrix(transformComp.ToMat4());
				shader->SetVPMatrix(_camera->GetVPMatrix());
				meshComp.Mesh->Draw(mat);
			}
		}
	}
}