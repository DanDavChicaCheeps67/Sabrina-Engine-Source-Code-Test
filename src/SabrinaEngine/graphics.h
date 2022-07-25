#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <iostream>
#include <SDL2/SDL.h>
#include "framerate.h"

const Uint32 DEFAULT_WINFLAG = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
             FULLSCREEN = SDL_WINDOW_FULLSCREEN, 
	     FAKE_FULLSCREEN = SDL_WINDOW_FULLSCREEN_DESKTOP,
	     USE_OPENGL = SDL_WINDOW_OPENGL,
	     USE_VULKAN = SDL_WINDOW_VULKAN,
	     BORDERLESS = SDL_WINDOW_BORDERLESS,
	     GRAB_INPUT = SDL_WINDOW_INPUT_GRABBED,
	     FOCUS_INPUT = SDL_WINDOW_INPUT_FOCUS,
	     MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
	     HIGH_DPI = SDL_WINDOW_ALLOW_HIGHDPI,
	     POPUP = SDL_WINDOW_POPUP_MENU,
	     FOREIGN = SDL_WINDOW_FOREIGN
	     ;

const Uint32 DEFAULT_RENFLAG = SDL_RENDERER_SOFTWARE,
             HARDWARE_REN = SDL_RENDERER_ACCELERATED,
	     VSYNC_SYNC = SDL_RENDERER_PRESENTVSYNC,
	     TARGET_TEXTURE = SDL_RENDERER_TARGETTEXTURE
	     ;

// Graphics Struct
typedef struct Window
{
	SDL_Window* window;
	SDL_Renderer *render;
	int renderIndex;
	SDL_Texture* backbuffer;
	short posX, posY, width, height;
	bool renderToBackbuffer;
	bool fullscreen;
	SDL_RendererFlip bufferFlip;
	Uint8 backgroundColor[4], changeBackbufferColor[4];
	float bufferAngle;
	std::string title;
	SDL_Event check;
	Uint32 winFlags, renFlags;
	short scaleFlag;
	SDL_DisplayMode displayMode;
	FrameRate rate;

} Window;

// initiate Graphics for entire engine
bool initGraphics();
bool windowSetup(Window*,short,short,std::string,Uint32,Uint32,int,short,bool,Uint8,Uint8,Uint8,Uint8,short);
SDL_Renderer *checkRenderFlags(Uint32&);
SDL_Texture *setBackBuffer(SDL_Renderer*, short&,short&);
void clearGraphics(Window*,SDL_Renderer*);
void updateRender(Window*,SDL_Renderer*);

//Draw Primitaves
void drawPixel(short,short,short,short,short,SDL_Renderer*);
void drawRect(short,short,short,short,short,short,short,SDL_Renderer*);
void drawOwnRect(SDL_Rect*,SDL_Renderer*,int,int,int,int);
void drawLine(short,short,short,short,SDL_Renderer*);
void drawCircle(short,short,short, SDL_Renderer*);
// Backbuffer changes
void changeBufferColor(SDL_Renderer*, Uint8*);

// Clear Memory
void destroyWindow(Window*);
void clearGraphics();
#endif
