/*
	The Sabrina Engine
	------------------
Start Date: March 24th, 2022
Arthor: Daniel A. Chicas 

Copyright (C) 2022 Daniel A. Chicas <CheepsDavChica1367@protonmail.com>

Purpose: Make a simple game instead of drowning oneself into a complicated river.

 This program is free software; you can redistribute it and/or modify 
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.


*/
// Sabrina Engine header files
#include "sabrinaEngine.h"

SabrinaEngine :: SabrinaEngine()
{
	// Init Everything
	if (initSDLMain() != false)
	{
		if(initGraphics() != false)
		{
			if(initSound() != false)
			{
				if(initInput() != false)
				{
					for (short i = 0; i < 10; i++)
						Windows[i].window = NULL;

					check = true;
				}
				else
				{
					printf("INPUT PROBLEM\n");
					check = false;
				}
			}else
			{
				printf("SOUND PROBLEM\n");
				check = false;
			}
		}else
		{
			printf("TROUBLE INITITATING GRAPHICS\n");
			check = false;
		}
	}else
	{
		printf("SDL can't initiate!\n");
		check = false;
	}
}

bool SabrinaEngine :: checkIfInitiated()
{
	return check;
}

bool SabrinaEngine :: initSDLMain()
{
	
	if (!SDL_Init(0))
		return true;
	else 
	{
		printf("SDL Error: %s\n",SDL_GetError());
		return false;
	}
}

bool SabrinaEngine :: setUpMainGraphics( short width, 
		        		 short height,
					 std::string title,
					 Uint32 winFlag,
					 Uint32 renFlag,
		  			 int renderIndex,
					 short scaleFlag,
					 bool renderToBackbuffer,
					 Uint8 backgroundColorR,
					 Uint8 backgroundColorG,
					 Uint8 backgroundColorB,
					 Uint8 backgroundColorA,
					 short fps
		                       )
{
	bool check = windowSetup( &Windows[0],
			          width,
				  height,
				  title,
				  winFlag,
				  renFlag,
				  renderIndex,
				  scaleFlag,
				  renderToBackbuffer,
				  backgroundColorR,
				  backgroundColorG,
				  backgroundColorB,
				  backgroundColorA,
				  fps
			        );
	if (check)
		windowCount++;
	return check;
}

bool SabrinaEngine :: setUpMainGraphicsDefault()
{
	bool check = windowSetup( &Windows[0],
		     			  320,
		     			  244,
		     		          "SABRINA ENGINE GAME",
		     			  DEFAULT_WINFLAG,
					  DEFAULT_RENFLAG,
					  -1,
		    			  0,
		     			  false,
		     			  244,
		                          136,
		                          252,
		                          1,
					  60
		   		 );
	if (check)
		windowCount++;

	return check;
}

bool SabrinaEngine :: setUpMainGraphicsFromFile(std::string location)
{
	settingsFile = location;

	// Read from file loaction
	return 0;
}

bool SabrinaEngine :: setUpNewWindow(short width, 
		        	     short height,
			             std::string title,
			             Uint32 winFlag,
			             Uint32 renFlag,
			             int renderIndex,
			             short scaleFlag,
			             bool renderToBackbuffer,
			             Uint8 backgroundColorR,
			             Uint8 backgroundColorG,
			             Uint8 backgroundColorB,
			             Uint8 backgroundColorA,
			             short fps
		                    )
{
	bool check;
	for (short i = 0; i < windowCount; i++)
	{
		if (Windows[i].window == NULL)
		{
			check = windowSetup( &Windows[i],
				             width,
					     height,
					     title,
					     winFlag,
					     renFlag,
					     renderIndex,
					     scaleFlag,
					     renderToBackbuffer,
					     backgroundColorR,
					     backgroundColorG,
				 	     backgroundColorB,
					     backgroundColorA,
					     fps
				           );
			break;
		}
	}

	return check;
}

bool SabrinaEngine :: mainLoop()
{
	return checkCloseWindow(&Windows[0]) ? false : true;
}

bool SabrinaEngine :: initMixerSystem(int soundRate, Uint16 format, int channels, int buffer)
{
	return initMixer(soundRate,format,channels,buffer);
}

SabrinaEngine :: ~SabrinaEngine()
{
	if (Windows[0].window != NULL)
		destroyWindow(&Windows[0]);
	clearGraphics();
	freeInput();
	if (mixer)
		freeMixer();
	destroyAudioSystem();
	SDL_Quit();
	printf("FREE\n");
}
