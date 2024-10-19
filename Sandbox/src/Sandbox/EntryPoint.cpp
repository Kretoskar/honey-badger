#include "Sandbox/Core/Public/Sandbox.h"

int main(int argc, char* argv[])
{
	Sandbox::Sandbox sandbox;
	if (sandbox.Init(1920, 1080, "Sandbox"))
	{
		sandbox.Start();
	}
}