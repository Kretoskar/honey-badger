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
		_editorUI->SetEntityMap(*_ecs);
	}
}