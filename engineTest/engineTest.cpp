#include <iostream>
#include "./src/SabrinaEngine/sabrinaEngine.h"
#include <SDL2/SDL.h>
#include <cstdlib>

/*bool initFrameRate(FrameRate* source)
{
	//bool worked = false;

	initTicks(&source->fpsTimer);
	initTicks(&source->capTimer);
	source->targetFrameRate = 60;
	source->ticksPerFrame = calTicksPerFrame(source->targetFrameRate);
	return true;
}
*/

bool initTestSprite(Sprite* source, Window* win)
{
	bool worked = false;

	source->spriteSheetLocation = "./assets/sprites/players/Sabrina/SabrinaSpritePixeledStandTest.bmp"; 
	source->alphaColor[0] = 0;
	source->alphaColor[1] = 110;
	source->alphaColor[2] = 206;
	source->alphaColor[3] = 1;

	if (loadSpriteSheetManual(source, win, &source->pixels) != false)
	{
		//printf("Pixel Status: %s\n", source->pixels);
		if(alphaColorRemovalSprites(source,win->window, &source->pixels))
		{
			//printf("ALPHA COLOR REMOVED\n");
			worked = true;
			source->spriteWidth = 48;
			source->spriteHeight = 48;
			source->frameWidth = source->sheetWidth;
			source->frameHeight = source->sheetHeight;
			source->frameNum = 0;
			source->flip = false;
			source->fliped = SDL_FLIP_NONE;
			source->angle = 0;
			source->xPos = win->WIDTH / 2;
			source->yPos = win->HEIGHT / 2;

		} else
			printf("ALPHA COLOR REMOVAL FAILED\n");

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

bool initMusic(MusicFile* source)
{
	bool worked = false;
	source->location = "./assets/sounds/levelMusic/EggGardenZone.mp3";
	source->channel = 1;
	source->maxVolume = 100;
	source->minVolume = 0;
	source->loop = true;

	if (openMusicFile(source) != false)
		worked = true;
	else
		printf("No sound\n");

	return worked;
}

int main (int args, char* argvs[])
{	
	// Window Proroties
	struct Window mainWin;

	mainWin.WIDTH = 256;
	mainWin.HEIGHT = 224;
	mainWin.winName = "TEST";

	mainWin.winFlag = 0;
	mainWin.renFlag = 0;
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

	mainWin.rate.FPS = 60;
	mainWin.rate.frameDelay = calFrameDelay(mainWin.rate.FPS);
	mainWin.rate.frameCounter = 0;
	mainWin.soundRate =  MIX_DEFAULT_FREQUENCY;
	mainWin.format = MIX_DEFAULT_FORMAT;
	mainWin.channels = 2;
	mainWin.buffer = 1024;

	printf("Hello World\n");
	if (initEngine(&mainWin) != false)
	{
		printf("WORKED\n");
		/* DEV NOTE:
		 * Sprite loding in a needed feature +
		 * Split sprite rect into four different rects
		 * Play some music for testing +
		 * Put all textures into one giant texture +
		 * Regulate Frame rate to 60 fps+ 
		 * Add Fonts raster and Spritebased
		 * Add Collison Detection with AABB and Sensor-Casting
		 * TileMap Loading Parsac
		 */
		struct Sprite testSprite;
		if (initTestSprite(&testSprite,&mainWin))
		{
			struct Input inputKeys;
			initInputKeys(&inputKeys);
			struct MusicFile music;
			if (initMusic(&music) != false)
			{
				struct MusicFile soundEffects[3];
				soundEffects[0].location = "./assets/sounds/effects/SonicCD/jump2.wav";
				soundEffects[1].location = "./assets/sounds/effects/SonicCD/05_Ring.wav";
				soundEffects[2].location = "./assets/sounds/effects/SonicCD/whistle1.wav";

				soundEffects[0].loop = false;
				soundEffects[1].loop = false;
				soundEffects[2].loop = false;

				soundEffects[0].channel = -1;
				soundEffects[1].channel = -1;
				soundEffects[2].channel = -1;

				for (short i = 0; i < 3; i++)
				{
					if (openSoundEffect(&soundEffects[i]) == false)
						printf("ERROR\n");
				}


			while (checkCloseWindow(&mainWin) == false)
			{
				updateInput(&inputKeys);
				
				updateStartTime(&mainWin.rate);
				//printf("Start Time: %d\n", mainWin.rate.startTime);
				mainWin.rate.frameCounter++;	
				
				// Input Values
				// Keyboard
				
				for (short i = 0; i < inputKeys.board.numOfKeys; i++)
				{
					if (inputKeys.board.keyState[i])
						printf("Key Pressed: %d\n",i);
					if (inputKeys.board.prevKeyState[i])
						printf("Prev Key Pressed: %d\n",i);
				}

				if (keyboardDown(&inputKeys.board, 79))
					testSprite.flip = true;
				else if (keyboardDown(&inputKeys.board, 80))
					testSprite.flip = false;

				// Play, Paused, and Resume Music
				if (keyboardHit(&inputKeys.board,4))
				{
					printf("TRUE\n");
					if (music.playing == false)
						playMusic(&music);
				}
				else if (keyboardHit(&inputKeys.board,19))
				{
					if (music.paused == false)
						pauseMusic(&music);
					else if (music.paused == true)
						unPauseMusic(&music);

				}
				
					if (keyboardHit(&inputKeys.board,29))
					{
						playSoundEffect(&soundEffects[0]);
						printf("PLAYED\n");
					}
					else if (keyboardHit(&inputKeys.board,27))
					{
						playSoundEffect(&soundEffects[1]);
					}
					else if (keyboardHit(&inputKeys.board,6))
					{
						playSoundEffect(&soundEffects[2]);
					}

				// Mouse 
				mouseDown(&inputKeys.mouse);

				// Show HAT Values
				for (short i = 0; i < inputKeys.numOfJoysticks; i++)
				{
					printf("Pad # %d Name: %s\n",i,inputKeys.pad[i].name);
					printf("NUM OF BUTTONS: %d\n", inputKeys.pad[i].numOfButtons);
					printf("NUM OF HATS: %d\n", inputKeys.pad[i].numOfHats);
					for (short h = 0; h < inputKeys.pad[i].numOfButtons; h++)
					{
						if (inputKeys.pad[i].buttonState[h] == 1)
							printf("Button Pressed: %d\n",h);
					}
					for (short h = 0; h < inputKeys.pad[i].numOfHats; h++)
					{
						printf("Pad # %d Hat Value: %d\n",i+1,inputKeys.pad[i].hatPressed[h]);
						//printf("Pad # %d prevHat Value:%d\n",i+1,inputKeys.pad[i].prevHatPressed[h]);
					}
					printf("NUM OF AXIS: %d\n",inputKeys.pad[i].numOfAxes);
					if (inputKeys.pad[i].numOfAxes > 0)
					{
						for (short h = 0; h < inputKeys.pad[i].numOfAxes; h++)
						{
							printf("Axes # %d Value: %d\n",h, inputKeys.pad[i].axis[h]);
							//printf("Axes # %d Prev Value: %d\n",h,inputKeys.pad[i].prevAxis[h]);
						}
					}
				}
				// HAT value is UP then move chacter Up + 1 once
				// if hatValuePressed is UP and prevHatValue is nothing: move up 1


				clearGraphics(&mainWin);
				
				makeBackgroundWhite(mainWin.WIDTH, mainWin.HEIGHT, mainWin.render);
				//changeBufferColor(mainWin.render, mainWin.changeBackbufferColor);

				renderSpriteFrame(&testSprite,mainWin.render);

				updateRender(&mainWin);

				updatePassedTime(&mainWin.rate);
				
				printf("Passed Time: %d\n", mainWin.rate.passedTime);
				delayFrame(&mainWin.rate);
				printf("FPS: %d\n", mainWin.rate.FPS);
				printf("FRAMES COUNTED: %d\n", mainWin.rate.frameCounter);
			}

			killInput(&inputKeys);
			if (music.close != true)
				closeMusicFile(&music);

			} else
				printf("NO MUSIC\n");
		} else
			printf("SPRITE INIT FALIED\n");

		closeEngine(&mainWin);
	} else
		printf("No\n");

	return 0;
}
