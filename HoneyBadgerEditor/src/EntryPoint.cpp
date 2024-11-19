#include "HoneyBadgerEditor/Core/Public/HoneyBadgerEditor.h"

int main(int argc, char* argv[]) 
{ 
	HoneyBadgerEditor::Editor editor;
	if (editor.Init())
	{
		editor.Start();
	}
}