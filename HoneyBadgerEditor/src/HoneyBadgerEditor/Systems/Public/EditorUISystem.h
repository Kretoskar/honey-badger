#pragma once

#include "HoneyBadgerCore/ECS/Public/ECS.h"

namespace HoneyBadgerEditor
{
	class EditorUI;

	class EditorUISystem : public HoneyBadger::System
	{
	public:
		void Init(EditorUI* editorUI);
		void Update();

	private:
		EditorUI* _editorUI;
	};
}