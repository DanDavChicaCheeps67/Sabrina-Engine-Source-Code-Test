#include "sound.h"

bool initSound()
{
	bool worked = false;
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0)
		printf("SDL Error: %s\n", SDL_GetError());
	else {
		if (Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,1024) > -1)
		{
			worked = true; 
			printf("TOOTOOT\n");
		} else {
			printf("MIX Error: %s\n",Mix_GetError());
		}
	}

	return worked;
}

void destroyMixAudioSystem()
{
	Mix_Quit();
	SDL_InitSubSystem(SDL_INIT_AUDIO);
}
