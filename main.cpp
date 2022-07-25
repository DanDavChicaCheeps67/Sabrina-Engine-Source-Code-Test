#include <iostream>
#include "./src/SabrinaEngine/sabrinaEngine.h"


int main (int args, char* argvs[])
{
	printf("HELLO WORLD\n");

	SabrinaEngine testGame;

	if (testGame.checkIfInitiated() == true)
		printf("WORK\n");

	return 0;
}

