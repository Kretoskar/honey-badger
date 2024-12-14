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
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"

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
				Material* mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByName("unlit_color").get();

				if (std::shared_ptr<Shader> shader = mat->GetShader())
				{
					shader->SetModelMatrix(transformComp.ToMat4() * model->_meshesLocalTransforms[i].ToMat4());
					shader->SetVPMatrix(_camera->GetVPMatrix());
					mesh->Draw(mat);
				}
			}
		}
	}
}