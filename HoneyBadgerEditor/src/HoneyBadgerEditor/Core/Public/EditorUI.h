#pragma once

#include "HoneyBadgerCore/Rendering/Public/UserInterface.h"

namespace HoneyBadgerEditor
{
	class Editor;

	class EditorUI : public HoneyBadger::UserInterface
	{
	public:
		static char SceneName[512];

		void SetEditorUI(Editor* editor)
		{
			_editor = editor;
		}

	protected:
		virtual void CreateWidgets() override;

	private:
		void CreateLoggerWidget();
		void CreateSceneWidget();
		void CreateDetailsWidget();
		void CreateToolbarWidget();

		Editor* _editor;
	};
}