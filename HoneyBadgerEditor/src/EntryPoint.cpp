#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/Window/Public/Window.h"

int main(int argc, char* argv[]) 
{ 
	HoneyBadger::Engine engine;
	HoneyBadger::Window window;

	window.Init(1920, 1080, "Honey Badger Editor");
	while (!window.GetShouldClose())
	{
		window.Update();
	}

	window.Shutdown();
}