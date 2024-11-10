#pragma once

#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"
#include "HoneyBadgerCore/Core/Public/HBString.h"
#include "HoneyBadgerCore/Rendering/Public/Camera.h"
#include "HoneyBadgerCore/Rendering/Public/DebugRenderer.h"
#include "HoneyBadgerEditor/Core/Public/EditorUI.h"

#include <memory>

namespace HoneyBadgerEditor
{
	class Editor
	{
	public:
		bool Init();
		void Start();
		void ShutDown();

	private:
		void ShutDown_Internal();

		bool _shouldClose = false;

		HoneyBadger::Engine _engine;
		HoneyBadger::Window _window;
		HoneyBadgerEditor::EditorUI _ui;

		// TODO: different way to handle non default ctors
		std::shared_ptr<HoneyBadger::Camera> _camera;
		std::shared_ptr<HoneyBadger::DebugRenderer> _debugRenderer;
	};
}