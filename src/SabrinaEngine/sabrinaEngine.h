#ifndef _SABRINAENGINE_H
#define _SABRINAENGINE_H

#define SDL_MAIN_HANDLED

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

// Standard Libaries 
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <SDL2/SDL.h>
// Sabrina Engine Depenencies
#include "camera.h"
#include "collision.h"
#include "entity.h"
#include "fonts.h"
#include "framerate.h"
#include "graphics.h"
#include "input.h"
#include "mathCal.h"
#include "scene.h"
#include "sound.h"
#include "sprites.h"
#include "state.h"
#include "tileMape.h"
#include "vector.h"

class SabrinaEngine
{
	private:
		// General
		bool check;
		// Windows
		Window Windows[10];
		short windowCount;
		std::string settingsFile;

	public:
		SabrinaEngine();
		bool checkIfInitiated();
		bool setUpMainGraphics(short,short,std::string,Uint32,Uint32,int,short,bool,Uint8,Uint8,Uint8,Uint8,short);
		bool setUpMainGraphicsDefault();
		bool setUpMainGraphicsFromFile(std::string);
		bool setUpNewWindow(short,short,std::string,Uint32,Uint32,int,short,bool,Uint8,Uint8,Uint8,Uint8,short);
		bool initSDLMain();
		bool mainLoop();
		bool initMixerSystem(int,Uint16,int,int);
		void freeAWindow(short);
		Window* getWindow(short);
		~SabrinaEngine();

};

#endif
