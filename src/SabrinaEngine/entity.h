#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.h"
#include "collision.h"
#include "sprites.h"

class Entity
{
	private:
		bool check;
		std::string *name;
		Sprite sprite;
		collisionBox *boxCollision;
		float *boxCollisionDistanceX, *boxCollisionDistanceY;
		short numOfCollisionBoxes;
		collisionSensor sensors[4];

	public:	
		// init Entity
		Entity(Window*,std::string,bool,int,int,int,int,int,int,int,short,int,int,int,int,bool);
		void initEntityAnimation(int,int,int,int,int);
		void updateEntityAnimation();
		void changeEntitySpriteColor(Uint8,Uint8,Uint8,SDL_Window*);
		bool setEntityBlendMode(bool,short);
		void alphaBlendEntity(Uint8);
		void moveEntity(float,float);
		void renderEntity(SDL_Renderer*,bool);
		void renderEntityCollisionBox(SDL_Renderer*,Uint8,Uint8,Uint8,Uint8);
		~Entity();
};

#endif
