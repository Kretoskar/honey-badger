#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

bool HoneyBadgerEditor::Editor::Init()
{
	if (!_engine.Init())
	{
		return false;
	}

	HoneyBadger::WindowInitSettings WindowInitSettings
	{
		"Honey Badger Editor",
		HoneyBadger::WindowState::Maximized,
		1920, 
		1080,
		1.0f / 6.0f,
		1.0f / 6.0f,
		1.0f / 14.0f,
		1.0f / 4.0f
	};

	if (!_window.Init(WindowInitSettings))
	{
		return false;
	}

	if (!_engine.InitAfterWindow())
	{
		return false;
	}

	if (!_ui.Init(_window.GetGlfwWindow()))
	{
		return false;
	}

	_camera = std::make_shared<HoneyBadger::Camera>(&_window, HoneyBadger::Vec3(1.0f, 1.0f, 1.0f));
	_camera->Init();
	_debugRenderer = std::make_shared<HoneyBadger::DebugRenderer>(_camera);
	_debugRenderer->Init();

	return true;
}
void HoneyBadgerEditor::Editor::Start()
{
	while (!_shouldClose && !_window.GetShouldClose())
	{
		_camera->Update();

		_ui.CreateFrame();
		_ui.Render();
		_debugRenderer->Render();
		_window.Update();
	}

	ShutDown_Internal();
}

void HoneyBadgerEditor::Editor::ShutDown()
{
	_shouldClose = true;
}

void HoneyBadgerEditor::Editor::ShutDown_Internal()
{
	_window.Shutdown();
}