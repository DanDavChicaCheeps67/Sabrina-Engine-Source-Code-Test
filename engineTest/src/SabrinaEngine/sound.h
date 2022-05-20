#ifndef _SOUND_H
#define _SOUND_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "openFiles.h"

//Music file class
struct MusicFile
{
	std::string location;
	Mix_Music* music;
	Mix_Chunk* soundEffect;
};

// initiate Sound for the entire engine
bool initSound();


// Free Memory
void destroyMixAudioSystem();
#endif
