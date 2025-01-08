#include "Sandbox/Core/Public/Sandbox.h"

int main(int argc, char* argv[])
{
	Sand::CarGame sandbox;
	if (sandbox.Init("Sandbox", "carTemp"))
	{
		sandbox.Start();
	}
}