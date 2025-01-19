#pragma once

#include <map>
#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/ECS/Public/ECS.h"
#include "HoneyBadgerCore/Rendering/Public/UserInterface.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"

struct ImVec2;

namespace HoneyBadgerEditor
{
	struct EntityRelationshipMap
	{
		std::map<HoneyBadger::Entity, HoneyBadger::HBString> _entityNamesMap;
		std::map< HoneyBadger::HBString, HoneyBadger::Entity> _namesEntityMap;
		std::map<HoneyBadger::Entity, HoneyBadger::Entity> _entityParentsMap;
		std::map<HoneyBadger::Entity, HoneyBadger::HBString> _rootEntites;

		void Clear()
		{
			_entityNamesMap.clear();
			_namesEntityMap.clear();
			_entityParentsMap.clear();
			_rootEntites.clear();
		}
	};

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

		void DrawEntityButton(HoneyBadger::Entity e, HoneyBadger::HBString name, ImVec2 sceneWindowSize, uint32_t depth);
		void SetEntityMap(HoneyBadger::ECS& ecs);

	protected:
		virtual void CreateWidgets() override;

	private:
		void CreateLoggerWidget();
		void CreateSceneWidget();
		void CreateDetailsWidget();
		void CreateToolbarWidget();
		void RemoveComponent(void* payload);

		EntityRelationshipMap _entityMap;
		Editor* _editor;

		HoneyBadger::Entity _selectedEntity;
		bool _anyEntitySelected = false;
	};
}