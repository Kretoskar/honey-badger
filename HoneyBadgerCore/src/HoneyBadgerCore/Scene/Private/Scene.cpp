#include "hbpch.h"
#include "HoneyBadgerCore/Scene/Public/Scene.h"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h""

#define INIT_COMPONENT(component, componentMap) \
if (component* c = Ecs.GetComponentPtr<component>(e)) \
{	\
	Data.componentMap[e] = *c; \
} \

#define LOAD_COMPONENT(component, componentMap) \
if (Data.componentMap.find(e) != Data.componentMap.end()) \
{ \
	component& tc = Ecs.AddComponent<component>(newE); \
	tc = Data.componentMap[e]; \
} \

HoneyBadger::Scene::Scene(ECS& Ecs)
{
	Data.Guid = GenerateGUID();

	for (Entity e : Ecs.LivingEntities)
	{
		Data.Entities.push_back(e);

		INIT_COMPONENT(TransformComponent, TransformComponentMap);
		INIT_COMPONENT(MeshComponent, MeshComponentMap);
		INIT_COMPONENT(NameComponent, NameComponentMap);
		INIT_COMPONENT(ModelComponent, ModelComponentMap);
		INIT_COMPONENT(DirectionalLightComponent, DirectionalLightComponentMap);
		INIT_COMPONENT(RigidbodyComponent, RigidbodyComponentMap);
		INIT_COMPONENT(SphereColliderComponent, SphereColliderComponentMap);
		INIT_COMPONENT(BoxCollisionComponent, BoxCollisionComponentMap);
	}
}

void HoneyBadger::Scene::InitECS(ECS& Ecs)
{
	for (Entity e : Data.Entities)
	{
		Entity newE = Ecs.CreateEntity();

		LOAD_COMPONENT(TransformComponent, TransformComponentMap);
		LOAD_COMPONENT(MeshComponent, MeshComponentMap);
		LOAD_COMPONENT(NameComponent, NameComponentMap);
		LOAD_COMPONENT(ModelComponent, ModelComponentMap);
		LOAD_COMPONENT(DirectionalLightComponent, DirectionalLightComponentMap);
		LOAD_COMPONENT(RigidbodyComponent, RigidbodyComponentMap);
		LOAD_COMPONENT(SphereColliderComponent, SphereColliderComponentMap);
		LOAD_COMPONENT(BoxCollisionComponent, BoxCollisionComponentMap);
	}
}

#undef INIT_COMPONENT
#undef LOAD_COMPONENT