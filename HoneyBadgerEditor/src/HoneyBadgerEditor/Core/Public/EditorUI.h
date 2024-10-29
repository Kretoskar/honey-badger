#pragma once

#include "HoneyBadgerCore/Rendering/Public/UserInterface.h"

namespace HoneyBadgerEditor
{
	class EditorUI : public HoneyBadger::UserInterface
	{
	protected:
		virtual void CreateWidgets() override;

	private:
		void CreateLoggerWidget();
	};
}