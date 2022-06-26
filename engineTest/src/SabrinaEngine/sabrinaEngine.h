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
#include "openFiles.h"
#include "framerate.h"

// Prototypes
// SDL Functions
bool initEngine(Window*);
bool initSDLMain();
void closeEngine(Window*);

#endif
