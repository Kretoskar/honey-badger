#include "hbpch.h"

#include "HoneyBadgerCore/ECS/Public/Systems/ModelRenderingSystem.h"
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
#include "HoneyBadgerCore/ECS/Public/Components/ModelComponent.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Model.h"

void HoneyBadger::ModelRenderingSystem::Register(ECS& ecs, Camera* camera)
{
	_camera = camera;

	REGISTER_SYSTEM()
	REGISTER_COMPONENT_IN_SYSTEM(TransformComponent)
	REGISTER_COMPONENT_IN_SYSTEM(ModelComponent)
}

void HoneyBadger::ModelRenderingSystem::Render()
{
	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		ModelComponent& modelComp = _ecs->GetComponent<ModelComponent>(entity);

		if (std::shared_ptr<ModelData> model = AssetsRegistry::Instance->GetModelByGuid(modelComp.Guid))
		{
			for (int32_t i = 0; i < model->_meshesGuids.size(); ++i)
			{
				std::shared_ptr<Mesh> mesh = AssetsRegistry::Instance->GetMeshByGuid(model->_meshesGuids[i]);

				// TODO: take material from component
				Material* mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByGuid(modelComp.MaterialsGuids[i]).get();
				if (!mat)
				{
					mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByName("track").get();
				}
				
				if (mat)
				{
					if (std::shared_ptr<Shader> shader = mat->GetShader())
					{
						MeshData md = mesh->GetData();

						shader->SetModelMatrix(transformComp.WorldMatrix * md._localTransform.ToMat4());
						shader->SetRotModelMatrix(transformComp.WorldRotMatrix * md._localTransform.ToRotMat4());
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
	}
}