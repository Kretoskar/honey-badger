#include "hbpch.h"

#include "HoneyBadgerCore/ECS/Public/Systems/BoxCollisionRenderingSystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/BoxCollisionComponent.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/Shader.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"
#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "glad/glad.h"

void HoneyBadger::BoxCollisionRenderingSystem::Register(ECS& ecs, Camera* camera)
{
	_camera = camera;

	REGISTER_SYSTEM()
	REGISTER_COMPONENT_IN_SYSTEM(TransformComponent)
	REGISTER_COMPONENT_IN_SYSTEM(BoxCollisionComponent)
}

void HoneyBadger::BoxCollisionRenderingSystem::Render()
{
	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		BoxCollisionComponent& boxColliderComp = _ecs->GetComponent<BoxCollisionComponent>(entity);
		std::shared_ptr<Mesh> mesh = AssetsRegistry::Instance->GetMeshByName("cube0");

		Material* mat = Engine::Instance->GetAssetsRegistry()->GetMaterialByName("unlit_color").get();
		if (std::shared_ptr<Shader> shader = mat->GetShader())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			Mat4 model = transformComp.WorldMatrix;
			shader->SetModelMatrix(model);
			shader->SetRotModelMatrix(transformComp.WorldRotMatrix);
			shader->SetVPMatrix(_camera->GetVPMatrix());

			mesh->Draw(mat);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}