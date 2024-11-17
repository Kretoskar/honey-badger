#include "hbpch.h"

#include "HoneyBadgerCore/ECS/Public/Systems/RenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"

#include "HoneyBadgerCore/Math/Public/Mat4.h"

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
			meshComp.Mesh->GetMaterial()->Shader->SetModelMatrix(transformComp.ToMat4());
			meshComp.Mesh->GetMaterial()->Shader->SetVPMatrix(_camera->GetVPMatrix());
			meshComp.Mesh->Draw();
		}
	}
}
