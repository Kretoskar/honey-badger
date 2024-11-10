#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"
#include "HoneyBadgerCore/Math/Public/Vec3.h"

bool HoneyBadgerEditor::Editor::Init()
{
	if (!_engine.Init())
	{
		return false;
	}

	if (!_window.Init("Honey Badger Editor", false))
	{
		return false;
	}

	if (!_ui.Init(_window.GetGlfwWindow()))
	{
		return false;
	}

	_camera = std::make_shared<HoneyBadger::Camera>(&_window, HoneyBadger::Vec3(0.0f, 1.0f, 0.0f));
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