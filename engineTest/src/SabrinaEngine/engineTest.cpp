#include <iostream>
#include "sabrinaEngine.h"
#include <SDL2/SDL.h>

int main (int args, char* argvs[])
{
	printf("Hello World\n");
	std::string name = "SABRINA_TEST";
	if (initEngine(name) != false)
	{
		printf("WORKED\n");
		// While loop to check is window needs to be closed
		// program ended with Segmentation fault
		clearGraphics();
		drawLine(20,20,45,45);

		closeEngine();
	}
	else
	{
		printf("No\n");
	}
	return 0;
}
