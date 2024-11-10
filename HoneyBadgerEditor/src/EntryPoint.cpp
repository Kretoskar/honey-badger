#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"

#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

#include <iostream>

int main(int argc, char* argv[]) 
{ 
	HoneyBadger::File file("shaders/debug.vert");

	std::cout << *file.GetFileContents();

	HoneyBadgerEditor::Editor editor;
	if (editor.Init())
	{
		editor.Start();
	}
}