#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "graphics.h"
#include "fonts.h"
#include "input.h"
#include "collision.h"
#include "sprites.h"
#include "sound.h"
#include "state.h"
#include "entity.h"
#include "tileMap.h"
#include "framerate.h"

class Scene
{
	private:
		State *states;
		Window *sceneWindows;
		TileMap map;
		MusicFile *soundEffects, *Music;	
		short windowIndex,entityCount;
		bool check;


	public:
		Scene(std::string,Window*);
		bool checkIfInitiated();
		bool addState(std::string);
		bool checkState(std::string);
		bool addMusic(std::string);
		bool addSoundEffect(std::string);
		void updateGraphics();
		~Scene();
};

#endif
