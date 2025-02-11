#include "hbpch.h"

#include "HoneyBadgerCore/ECS/Public/Systems/RenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"

#include "HoneyBadgerCore/Math/Public/Mat4.h"

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"

void HoneyBadger::RenderingSystem::Register(ECS& ecs, Camera* camera)
{
	_camera = camera;
	
	REGISTER_SYSTEM()
	REGISTER_COMPONENT_IN_SYSTEM(TransformComponent)
	REGISTER_COMPONENT_IN_SYSTEM(NameComponent)
	REGISTER_COMPONENT_IN_SYSTEM(MeshComponent)
}

void HoneyBadger::RenderingSystem::Render()
{
	// TODO: properly implement this
	std::vector<Entity> transparentMaterialEntities;

	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		MeshComponent& meshComp = _ecs->GetComponent<MeshComponent>(entity);
		std::shared_ptr<Mesh> mesh = AssetsRegistry::Instance->GetMeshByGuid(meshComp.MeshGuid);

		if (mesh)
		{
			// TODO: take material from component
			Material* mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByGuid(meshComp.MaterialGuid.c_str()).get();
			if (!mat)
			{
				mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByName("unlit_color").get();
			}

			std::string matName = Engine::Instance->GetAssetsRegistry()->GetMaterialName(meshComp.MaterialGuid.c_str()).Get();
			if (matName.substr(matName.size() - 2) != "_t")
			{
				if (std::shared_ptr<Shader> shader = mat->GetShader())
				{
					shader->SetModelMatrix(transformComp.WorldMatrix);
					shader->SetRotModelMatrix(transformComp.WorldRotMatrix);
					shader->SetVPMatrix(_camera->GetVPMatrix());

					if (Texture* tex = Engine::Instance->GetAssetsRegistry()->GetTextureByName(mat->GetDiffuseMapName()).get())
					{
						shader->AssignDiffuseMap(*tex);
					}

					mesh->Draw(mat);
				}
			}
			else
			{
				transparentMaterialEntities.push_back(entity);
			}
		}
	}

	for (Entity entity : transparentMaterialEntities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		MeshComponent& meshComp = _ecs->GetComponent<MeshComponent>(entity);
		std::shared_ptr<Mesh> mesh = AssetsRegistry::Instance->GetMeshByGuid(meshComp.MeshGuid);

		if (mesh)
		{
			Material* mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByGuid(meshComp.MaterialGuid.c_str()).get();
			
			if (std::shared_ptr<Shader> shader = mat->GetShader())
			{
				shader->SetModelMatrix(transformComp.WorldMatrix);
				shader->SetRotModelMatrix(transformComp.WorldRotMatrix);
				shader->SetVPMatrix(_camera->GetVPMatrix());

				if (Texture* tex = Engine::Instance->GetAssetsRegistry()->GetTextureByName(mat->GetDiffuseMapName()).get())
				{
					shader->AssignDiffuseMap(*tex);
				}

				mesh->Draw(mat);
			}
		}
	}
}