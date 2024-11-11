#include "Sandbox/Core/Public/Sandbox.h"

int main(int argc, char* argv[])
{
	Sandbox::Sandbox sandbox;
	if (sandbox.Init("Sandbox"))
	{
		sandbox.Start();
	}
}