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
#include "HoneyBadgerCore/ECS/Public/Components/MeshComponent.h"
#include "HoneyBadgerCore/ECS/Public/Components/TransformComponent.h"
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
	// TODO: rewrite this shit
	std::unordered_map<HBString, TransformComponent*, HBString::HBStringHasher> EntityTransformMap;
	for (Entity entity : _entities)
	{
		TransformComponent& transformComp = _ecs->GetComponent<TransformComponent>(entity);
		NameComponent& nameComp = _ecs->GetComponent<NameComponent>(entity);
		EntityTransformMap.emplace(nameComp.Name, &transformComp);
	}

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

			if (std::shared_ptr<Shader> shader = mat->GetShader())
			{

				// TODO: For the love of God, rewrite this shit recursively
				bool hasParent = false;
				Mat4 parentMat;
				Mat4 parentRotMat;

				if (EntityTransformMap.find(EntityTransformMap[transformComp.Parent]->Parent) != EntityTransformMap.end()
					&& !EntityTransformMap[transformComp.Parent]->Parent.empty())
				{
					hasParent = true;
					parentMat = EntityTransformMap[EntityTransformMap[transformComp.Parent]->Parent]->ToMat4();
					parentRotMat = EntityTransformMap[EntityTransformMap[transformComp.Parent]->Parent]->ToRotMat4();
				}

				Mat4 modelMat;
				Mat4 RotModelMat;

				if (hasParent)
				{
					modelMat = EntityTransformMap.find(transformComp.Parent) == EntityTransformMap.end() ?
						transformComp.ToMat4() :
						parentMat * EntityTransformMap[transformComp.Parent]->ToMat4() * transformComp.ToMat4();

					RotModelMat = EntityTransformMap.find(transformComp.Parent) == EntityTransformMap.end() ?
						transformComp.ToRotMat4() :
						parentRotMat * EntityTransformMap[transformComp.Parent]->ToRotMat4() * transformComp.ToRotMat4();
				}
				else
				{
					modelMat = EntityTransformMap.find(transformComp.Parent) == EntityTransformMap.end() ?
						transformComp.ToMat4() :
						EntityTransformMap[transformComp.Parent]->ToMat4() * transformComp.ToMat4();

					RotModelMat = EntityTransformMap.find(transformComp.Parent) == EntityTransformMap.end() ?
						transformComp.ToRotMat4() :
						EntityTransformMap[transformComp.Parent]->ToRotMat4() * transformComp.ToRotMat4();
				}

				shader->SetModelMatrix(modelMat);
				shader->SetRotModelMatrix(RotModelMat);
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