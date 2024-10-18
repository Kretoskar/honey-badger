#include "HoneyBadgerCore/Window/Public/Window.h"

int main(int argc, char* argv[]) 
{ 
	HoneyBadger::Window window;
	window.Init();
	while (true)
	{
		window.Update();
	}



}