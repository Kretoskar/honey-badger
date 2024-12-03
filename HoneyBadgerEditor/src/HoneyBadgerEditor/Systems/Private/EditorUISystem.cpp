#include "HoneyBadgerEditor/Systems/Public/EditorUISystem.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"

using namespace HoneyBadger;

namespace HoneyBadgerEditor
{
	void EditorUISystem::Register(ECS& ecs, EditorUI* editorUI)
	{
		_editorUI = editorUI;

		REGISTER_SYSTEM()
		REGISTER_COMPONENT_IN_SYSTEM(NameComponent)
	}

	void EditorUISystem::Update()
	{
		// TODO: Only trigger when ECS dirty

		std::map<Entity, HBString> entityMap;


		for (Entity entity : _entities)
		{
			NameComponent& name = _ecs->GetComponent<NameComponent>(entity);

			entityMap.insert({ entity, name.Name });
		}

		_editorUI->SetEntityMap(std::move(entityMap));
	}
}