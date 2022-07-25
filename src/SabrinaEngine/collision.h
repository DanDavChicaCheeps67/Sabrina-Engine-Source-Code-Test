#ifndef _COLLISION_H
#define _COLLISION_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>

typedef struct collisionBox
{
	float xPos, yPos;
	int width, height;
	short right, left, top, bottom;
	SDL_Rect Box;
	Uint8 color[4];
	bool touched;
} collisionBox;

typedef struct collisionSensor
{
	float xPos, yPos;
	SDL_Point point;
} collisionSensor;

// Init Collision Box
void initCollisionBox(collisionBox*,float,float,int,int);
void initSensor(collisionSensor*,float,float);
void addColor(collisionBox*,Uint8,Uint8,Uint8,Uint8);
// Check if two boxes collided
bool checkCollision(collisionBox*,collisionBox*);
// Transfer data to SDL_Rect
void toSDLRect(collisionBox*);
void toSDLPoint(collisionSensor*);

#endif
