#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"

bool HoneyBadgerEditor::HoneyBadgerEditor::Init(uint32_t width, uint32_t height, HoneyBadger::HBString name)
{
	if (!_engine.Init())
	{
		return false;
	}

	if (!_window.Init(width, height, name))
	{
		return false;
	}

	return true;
}
void HoneyBadgerEditor::HoneyBadgerEditor::Start()
{
	while (!_shouldClose && !_window.GetShouldClose())
	{
		_window.Update();
	}

	ShutDown_Internal();
}

void HoneyBadgerEditor::HoneyBadgerEditor::ShutDown()
{
	_shouldClose = true;
}

void HoneyBadgerEditor::HoneyBadgerEditor::ShutDown_Internal()
{
	_window.Shutdown();
}