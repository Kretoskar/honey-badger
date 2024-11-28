#include "HoneyBadgerEditor/Systems/Public/EditorUISystem.h"
#include "HoneyBadgerEditor/Core/Public/EditorUI.h"
#include "HoneyBadgerCore/ECS/Public/Components/NameComponent.h"

using namespace HoneyBadger;

namespace HoneyBadgerEditor
{
	void EditorUISystem::Init(EditorUI* editorUI)
	{
		_editorUI = editorUI;
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