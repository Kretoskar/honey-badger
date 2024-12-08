#pragma once

#include <map>
#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"
#include "HoneyBadgerCore/Rendering/Public/UserInterface.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"

namespace HoneyBadgerEditor
{
	class Editor;

	class EditorUI : public HoneyBadger::UserInterface
	{
	public:
		static char SceneName[512];

		void SetEditorUI(Editor* editor)
		{
			HB_BIND_EVENT(HoneyBadger::RemoveComponentEvent::Type(), RemoveComponent)
			_editor = editor;
		}


		void SetEntityMap(std::map<HoneyBadger::Entity, HoneyBadger::HBString> map);

	protected:
		virtual void CreateWidgets() override;

	private:
		void CreateLoggerWidget();
		void CreateSceneWidget();
		void CreateDetailsWidget();
		void CreateToolbarWidget();
		void RemoveComponent(void* payload);

		Editor* _editor;

		std::map<HoneyBadger::Entity, HoneyBadger::HBString> _entityMap;
		HoneyBadger::Entity _selectedEntity;
		bool _anyEntitySelected = false;
	};
}