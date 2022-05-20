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

bool initEngine(Window* win)
{
	bool worked = false;
	//short settingsFlags[sizeof(short)];
	//std::string settings = "engine_settings.txt";
	//openSettingsFile(settings, settingsFlags);
	
	// Init Everything
	if (initSDLMain() != false)
	{
		if(initGraphics(win) != false)
		{
			if(initSound() != false)
			{
				if(initInput() != false)
				{
					worked = true;
				} else
					printf("INPUT PROBLEM\n");
			}else 
				printf("SOUND PROBLEM\n");
		}else
			printf("TROUBLE INITITATING GRAPHICS\n");
	}else
		printf("SDL can't initiate!\n");
	
	return worked;
}

bool initSDLMain()
{
	bool worked = false;
	
	if (!SDL_Init(0))
		worked = true;
	else 
		printf("SDL Error: %s\n",SDL_GetError());

	return worked;
}

void closeEngine(Window *win)
{
	destroyGraphics(win);
	freeInput();
	destroyMixAudioSystem();
	SDL_Quit();
}
