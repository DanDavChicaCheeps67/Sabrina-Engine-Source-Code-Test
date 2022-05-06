#include <iostream>
#include "./src/SabrinaEngine/sabrinaEngine.h"
#include <SDL2/SDL.h>
#include <cstdlib>

int main (int args, char* argvs[])
{
	// Random Numbers
	srand(time(0));

	// Window Proroties
	Window mainWin;
	mainWin.window = NULL;
	mainWin.render = NULL;
	mainWin.WIDTH = 320;
	mainWin.HEIGHT = 224;
	mainWin.renFlag = 0;
	mainWin.winFlag = 0;
	mainWin.winName = "SABRINA_TEST";

	printf("Hello World\n");
	if (initEngine(&mainWin) != false)
	{
		printf("WORKED\n");
		/* DEV NOTE:
		 * Sprite loding in a needed feature
		 * Play some music for testing
		 * Put all textures into one giant texture
		 * Regulate Frame rate to 60 fps
		 * Add Fonts raster and Spritebased
		 * Add Collison Detection with AABB and Sensor-Casting
		 * TileMap Loading Parsac
		 */

		while (checkCloseWindow(&mainWin) == false)
		{
			clearGraphics(&mainWin);
			drawLine(rand()%mainWin.WIDTH,
				 rand()%mainWin.HEIGHT,
				 rand()%mainWin.WIDTH,
				 rand()%mainWin.HEIGHT,
				 mainWin.render);

			drawRect(rand()%mainWin.WIDTH,
				 rand()%mainWin.HEIGHT,
				 rand(),
				 rand(),
				 rand(),
				 rand(),
				 rand(),
				 mainWin.render);

			updateRender(&mainWin);
		}

		closeEngine(&mainWin);
	}
	else
	{
		printf("No\n");
	}
	return 0;
}
