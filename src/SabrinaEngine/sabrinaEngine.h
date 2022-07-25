#ifndef _SABRINAENGINE_H
#define _SABRINAENGINE_H

#define SDL_MAIN_HANDLED

// Standard Libaries 
#include <iostream>
#include <fstream>
#include <stdlib.h>
	// SDL
#include <SDL2/SDL.h>

// Sabrina Engine Depenencies
	// Graphics
#include "graphics.h"
#include "sprites.h"
/*
#include "fonts.h"
#include "tileMap.h"
*/

#include "sound.h"
#include "input.h"
#include "framerate.h"
#include "collision.h"
#include "entity.h"

class SabrinaEngine
{
	private:
		// General
		bool check;
		// Windows
		Window Windows[10];
		short windowCount;
		std::string settingsFile;

		// Sound 
		int soundRate, format, channels, buffer;
		bool mixer;
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
		~SabrinaEngine();

};

#endif
