#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>
#include "framerate.h"

typedef SDL_Renderer* Render;

// Graphics Struct
struct Window
{
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* backbuffer;
	short posX, posY, WIDTH, HEIGHT;
	short winFlag, renFlag, scaleFlag;
	bool renderToBackbuffer;
	SDL_RendererFlip bufferFlip;
	Uint8 backgroundColor[3], changeBackbufferColor[4];
	float bufferAngle;
	std::string winName;
	FrameRate rate;
	SDL_Event check;
	// Sound 
	int soundRate, format, channels, buffer;
};

// initiate Graphics for entire engine
bool initGraphics(Window*);
SDL_Window *checkWindowFlag(std::string&,short&, short&, short&);
SDL_Renderer *checkRenderFlags(Window*);
SDL_Texture *setBackBuffer(SDL_Renderer*, short&,short&);
void clearGraphics(Window*);
void updateRender(Window*);

//Draw Primitaves
void drawPixel(short&,short&,short&,short&,short&,SDL_Renderer*);
void drawRect(short,short,short,short,short,short,short,SDL_Renderer*);
void drawLine(short,short,short,short,SDL_Renderer*);

// Backbuffer changes
void changeBufferColor(SDL_Renderer*, Uint8*);

// Clear Memory
void destroyGraphics(Window*);
#endif
