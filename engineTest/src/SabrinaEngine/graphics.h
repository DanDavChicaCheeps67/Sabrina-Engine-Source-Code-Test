#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>

// Graphics Struct
struct Window
{
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* backbuffer;
	short posX, posY, WIDTH, HEIGHT;
	short winFlag, renFlag, scaleFlag, bufferFlip;
	float bufferAngle;
	std::string winName;
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

// Clear Memory
void destroyGraphics(Window*);
#endif
