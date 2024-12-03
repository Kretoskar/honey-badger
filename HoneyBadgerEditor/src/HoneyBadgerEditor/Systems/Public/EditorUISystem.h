#pragma once

#include "HoneyBadgerEditor/Core/Public/EditorUI.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadgerEditor
{
	class EditorUISystem : public HoneyBadger::System
	{
	public:
		void Register(HoneyBadger::ECS& ecs, EditorUI* editorUI);
		void Update();

	private:
		EditorUI* _editorUI;
	};
}