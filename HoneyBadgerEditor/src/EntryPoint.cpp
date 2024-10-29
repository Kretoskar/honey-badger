#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"

int main(int argc, char* argv[]) 
{ 
	HoneyBadgerEditor::Editor editor;
	if (editor.Init(1920, 1080, "Honey Badger Editor"))
	{
		editor.Start();
	}
}