#ifndef _SPRITES_H
#define _SPRITES_H

#include <iostream>
#include <SDL2/SDL.h>

#include "graphics.h"
#include "openFiles.h"

struct Sprite
{
	// For Sprite Animation
	short frameNum, maxFrames;
	int frameWidth, frameHeight, spriteWidth, spriteHeight;
	SDL_Texture *spriteSheet;
	std::string spriteSheetLocation;
	int sheetWidth, sheetHeight;
	SDL_Rect pos;
	// Sprite in the world
	float xPos, yPos;
	SDL_RendererFlip flip;
	float angle;
	// Texture Manipulation
	bool changeWholeColor; 
	Uint32 format;
	short pitch, textAccess;
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
// Load SpriteSheets
bool loadSpriteSheet(Sprite*,SDL_Renderer*);

// Render texture to screen
void renderSpriteFrame(Sprite*, SDL_Renderer*);
void renderBackForeToScreen(BackForeGround*, SDL_Renderer*);

// Lock texture to render specific color palette
bool lockTexture(SDL_Texture*,short*,void**);
bool unlockTexture(SDL_Texture*,short*,void**);
bool alphaColorRemovalSprites(Sprite*, SDL_Window*);
void alphaColorRemoval(SDL_Window*,SDL_Texture*,Uint8*,short&,void**,float&,float&);
void changeColor(SDL_Window*,SDL_Texture*,Uint8*,bool&,short&,void**,float&,float&);

// Lock Texture to blend
void alphaBlend(SDL_Texture*,Uint8&);
// Free sprite memory
void freeSprite(Sprite*);
// Free Background memory
void freeBackFore(BackForeGround*);

#endif
