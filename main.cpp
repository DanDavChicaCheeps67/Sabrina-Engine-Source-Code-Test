#include <iostream>
#include "./src/SabrinaEngine/sabrinaEngine.h"


int main (int args, char* argvs[])
{
	printf("HELLO WORLD\n");

	SabrinaEngine testGame;

	if (testGame.checkIfInitiated() == true)
	{
		if ( testGame.setUpMainGraphicsDefault() )
		{
			if (testGame.initMixerSystem())
			{
				while(testGame.mainLoop())
				{
					// Add Scene loop and state loop				
				}
			}
			else
				printf("Failed to Setup MIxer\n");
		}
		else
			printf("Failed to Setup Graphics\n");
	}

	return 0;
}

