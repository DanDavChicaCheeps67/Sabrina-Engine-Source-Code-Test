#ifndef _SPRITES_H
#define _SPRITES_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "graphics.h"
#include "openFiles.h"
#include "framerate.h"

struct Sprite
{
	// For Sprite Animation
	short firstFrame, frameNum, maxFrames;
	int frameWidth, frameHeight, delay, delayCounter, spriteWidth, spriteHeight;
	SDL_Texture *spriteSheet;
	std::string spriteSheetLocation;
	short sheetWidth, sheetHeight;
	SDL_Rect pos;
	// Sprite in the world
	float xPos, yPos;
	bool flip;
	SDL_RendererFlip fliped;
	float angle;
	// Texture Manipulation
	bool changeWholeColor; 
	Uint32 format;
	int pitch, textAccess;
	void *pixels;
	Uint8 colorChage[3], colorTarget[3], alphaColor[4], alphaLevels;
};

struct BackForeGround
{
	short width, height, xPos, yPos; 
	SDL_RendererFlip flip;
	float angle;
	std::string location;
	SDL_Texture *image;
	SDL_Rect pos;
	bool changeWholeColor;
	short pitch;
	void *pixels;
	Uint8 colorChange[3], colorTarget[3], alphaColor[3], alphaLevels;
};
// Init Sprite
bool initSprite(Sprite*,std::string,bool,int,int,int,int,int,int,int);
void initAnimation(Sprite*,int,int);

// Load SpriteSheets
bool loadSpriteSheet(Sprite*,SDL_Renderer*);
bool loadSpriteSheetManual(Sprite*,Window*,void**);

//Update Sprite
void updateSprite(Sprite*);

// Render texture to screen
void renderSpriteFrame(Sprite*, SDL_Renderer*);
void renderBackForeToScreen(BackForeGround*, SDL_Renderer*);

// Lock texture to render specific color palette
bool lockTexture(SDL_Texture*,int*,void**);
bool unlockTexture(SDL_Texture*,short*,void**);
bool alphaColorRemovalSprites(Sprite*, SDL_Window*,void**);
void alphaColorRemoval(SDL_Window*,SDL_Texture*,Uint8*,short&,void**,float&,float&);
void changeColor(SDL_Window*,SDL_Texture*,Uint8*,bool&,int&,void**,float&,float&);

// Lock Texture to blend
void alphaBlend(SDL_Texture*,Uint8&);
// Free sprite memory
void freeSprite(Sprite*);
// Free Background memory
void freeBackFore(BackForeGround*);

#endif
