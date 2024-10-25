#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

int main(int argc, char* argv[]) 
{ 
	HoneyBadger::Engine _engine;
	if (!_engine.Init())
	{

	}

	HoneyBadger::Window _window;

	_window.Init(1920, 1080, "Honey Badger Editor");
	while (!_window.GetShouldClose())
	{
		_window.Update();
	}

	_window.Shutdown();
}