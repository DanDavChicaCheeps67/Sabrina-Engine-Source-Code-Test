#ifndef _SPRITES_H
#define _SPRITES_H

#include <iostream>
#include <SDL2/SDL.h>

#include "graphics.h"
#include "openFiles.h"

struct Sprite
{
	// For Sprite Animation
	short spriteWidth, spriteHeight, rowNumToRender, numOfSpritesInRow, frameInRow;
	SDL_Texture *spriteSheet;
	std::string spriteSheetLocation;
	short sheetWidth, sheetHeight;
	SDL_Rect pos;
	// Sprite in the world
	short xPos, yPos, flip;
	float angle;
	// Texture Manipulation
	bool changeWholeColor; 
	short pitch;
	void *pixels;
	Uint8 colorChage[3], colorTarget[3], alphaColor[3], alphaLevels;
};

struct BackForeGround
{
	short width, height, xPos, yPos, flip;
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
// 	state tile size for each individual sprite
// 	Inital start position
// 	Alpha Color
// Render texture to screen
void renderSpriteFrame(Sprite*, SDL_Renderer*);
void renderBackForeToScreen(BackForeGround*, SDL_Renderer*);
// Lock texture to render specific color palette
bool lockTexture(SDL_Texture*,short&,void&);
bool unlockTexture(SDL_Texture*,short&,void&);
void alphaColorRemoval(SDL_Window*,SDL_Texture*,Uint8*,short&,void&,short&,short&);
void changeColor(SDL_Window*,SDL_Texture*,Uint8*,bool&,short&,void&,short&,short&);
// Lock Texture to blend
void alphaBlend(SDL_Texture*,Uint8&);
// Free sprite memory
void freeSprite(Sprite*);
// Free Background memory
void freeBackFore(BackForeGround*);

#endif
