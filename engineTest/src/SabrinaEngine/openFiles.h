#ifndef _OPENFILES_H
#define _OPENFILES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <fstream>

void openSettingsFile(std::string&,short*);
void openSaveFile(std::string&);
// Open Graphical Files
SDL_Texture* loadMedia(SDL_Window*,SDL_Renderer*, std::string);
// Open Sound Files
Mix_Music* loadMusic(std::string&);
Mix_Chunk* loadSoundEffect(std::string&);

#endif
