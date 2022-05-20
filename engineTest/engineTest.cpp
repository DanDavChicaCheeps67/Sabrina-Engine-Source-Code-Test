#include <iostream>
#include "./src/SabrinaEngine/sabrinaEngine.h"
#include <SDL2/SDL.h>
#include <cstdlib>

bool initTestSprite(Sprite* source, Window* win)
{
	bool worked = false;

	source->spriteSheetLocation = "sonicStand.bmp"; 
	source->alphaColor[0] = 0;
	source->alphaColor[1] = 110;
	source->alphaColor[2] = 206;
	source->alphaColor[3] = 1;

	if (loadSpriteSheet(source, win->render) != false)
	{
		worked = true;
		source->spriteWidth = 48;
		source->spriteHeight = 48;
		source->frameWidth = source->sheetWidth;
		source->frameHeight = source->sheetHeight;
		source->frameNum = 0;
		source->flip = SDL_FLIP_NONE;
		source->angle = 0;
		source->xPos = 69;
		source->yPos = 69;
	} else
		printf("CAN'T LOAD\n");

	return worked;
}

void makeBackgroundWhite(short &width, short &height, Render &ren)
{
	drawRect( 0,
		  0,
		  width,
		  height,
		  255,
		  255,
		  255,
		  ren
		);
}


int main (int args, char* argvs[])
{
	// Random Numbers

	// Window Proroties
	struct Window mainWin;

	mainWin.WIDTH = 256;
	mainWin.HEIGHT = 224;
	mainWin.winName = "TEST";

	mainWin.winFlag = 0;
	mainWin.renFlag = 2;
	mainWin.scaleFlag = 1;
	mainWin.renderToBackbuffer = true;

	mainWin.backgroundColor[0] = 0;
	mainWin.backgroundColor[1] = 0;
	mainWin.backgroundColor[2] = 255;

	mainWin.changeBackbufferColor[0] = 255;
	mainWin.changeBackbufferColor[1] = 255;
	mainWin.changeBackbufferColor[2] = 255;
	mainWin.changeBackbufferColor[3] = 1;
	mainWin.bufferFlip = SDL_FLIP_NONE;

	printf("Hello World\n");
	if (initEngine(&mainWin) != false)
	{
		printf("WORKED\n");
		/* DEV NOTE:
		 * Sprite loding in a needed feature +
		 * Split sprite rect into four different rects
		 * Play some music for testing
		 * Put all textures into one giant texture +
		 * Regulate Frame rate to 60 fps 
		 * Add Fonts raster and Spritebased
		 * Add Collison Detection with AABB and Sensor-Casting
		 * TileMap Loading Parsac
		 */

		struct Sprite testSprite;
		if (initTestSprite(&testSprite,&mainWin))
		{
			while (checkCloseWindow(&mainWin) == false)
			{
				/*
				 * MAKE SURE DEST RECT HAS A WIDTH AND HEIGHT VALUE
				 * WHEN RENDERING WITH SDL_RENDERCOPY
				 */

				clearGraphics(&mainWin);	
				
				makeBackgroundWhite(mainWin.WIDTH, mainWin.HEIGHT, mainWin.render);
				//changeBufferColor(mainWin.render, mainWin.changeBackbufferColor);
					
				renderSpriteFrame(&testSprite,mainWin.render);
				
				/*
				SDL_Rect frame, dest;

				frame.x = 0;
				frame.y = 0;
				frame.w = 28;
				frame.h = 39;

				dest.x = 64;
				dest.y = 64;
				dest.w = 56;
				dest.h = 78;

				SDL_RenderCopy( mainWin.render, testSprite.spriteSheet,&frame,&dest);
				*/

				updateRender(&mainWin);
			}
		} else
			printf("SPRITE INIT FALIED\n");

		closeEngine(&mainWin);
	}
	else
		printf("No\n");

	return 0;
}
