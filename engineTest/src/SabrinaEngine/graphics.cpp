#include "graphics.h"

bool initGraphics(Window* win)
{
	bool worked = false;

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
		printf("SDL ERROR: %s\n", SDL_GetError());
	else
	{
		win->window = checkWindowFlag(win->winName, win->WIDTH, win->HEIGHT, win->winFlag);

		if (win->window != NULL)
		{
			win->render = checkRenderFlag(win);
			if (win->render != NULL)
			{
				win->backbuffer = setBackBuffer(win->WIDTH,win->HEIGHT);
				SDL_RenderSetLogicalSize(win->render,win->WIDTH,win->HEIGHT);
				printf("SONIC\n");
				worked = true;
			}
			else
				printf("SDL ERROR: %s\n", SDL_GetError());
		} else
			printf("SDL ERROR: %s\n", SDL_GetError());
	}

	return worked;
}

SDL_Window *checkWindowFlag(std::string &name, short &WIDTH, short &HEIGHT, short &flag)
{
	SDL_Window *returned = NULL;

	switch (flag)
	{
		default: returned = SDL_CreateWindow( name.c_str(),
						      SDL_WINDOWPOS_UNDEFINED,
						      SDL_WINDOWPOS_UNDEFINED,
						      WIDTH,
						      HEIGHT,
						      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
						    );
			 break;

	}

	return returned;
}

SDL_Renderer *checkRenderFlags(Window* win)
{
	SDL_Renderer* returned = NULL;

	switch (win->scaleFlag)
	{
		case 1:
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear"); break;
		case 2:
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"best"); break;
		default:
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"nearest"); break;
	}

	switch (win->renFlag)
	{
		case 0:
			returned = SDL_CreateRenderer( win->window,
					               -1,
					               SDL_RENDERER_ACCELERATED
					  	     );
			printf("CD\n");
			break;

		default:
			returned = SDL_CreateRenderer( win->window,
					    	       -1,
					    	       SDL_RENDERER_SOFTWARE
					  	     );
			printf("SOFT");
			break;
	}

	return returned;
}

SDl_Texture *setBackBuffer(SDL_Renderer *ren, short &width, short &height)
{
	SDL_Texture *buff = SDL_CreateTexture( ren,
					      SDL_PIXELFORMAT_ARGB8888,
					      SDL_TEXTUREACCESS_STREAMING,
					      width,
					      height
					     );
	return buff;
}

void clearGraphics(Window *win)
{
	SDL_SetRenderTarget(win->render, win->backbuffer);
	SDL_SetRenderDrawColor(win->render,0,0,255,1);
	SDL_RenderClear(win->render);	
}

void updateRender(Window *win)
{
	// Restart Target
	SDL_SetRenderTarget(win->render, NULL);
	
	// Rendering BackBuffer
	SDL_RenderCopyEx( win->render,
			  win->backbuffer,
			  NULL,
			  NULL,
			  win->bufferAngle,
			  NULL,
			  win->bufferFlip
			);
	
	SDL_RenderPresent(win->render);
}

void destroyGraphics(Window *win)
{
	SDL_DestroyRenderer(win->render);
	SDL_DestroyWindow(win->window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void drawPixel( short &x,
		short &y,
		short &r,
		short &g,
		short &b,
		SDL_Renderer *render
	      )
{
	SDL_SetRenderDrawColor(render,r,g,b,0);
	SDL_RenderDrawPoint(render,x,y);
}

void drawLine( short x,
	       short y,
	       short x2,
	       short y2,
	       SDL_Renderer *render
	     )
{
	SDL_SetRenderDrawColor(render,255,255,255,0);
	SDL_RenderDrawLine(render,x,y,x2,y2);
	printf("LINELINE\n");
}

void drawRect( short x,
	       short y,
	       short width,
	       short height,
	       short r,
	       short g,
	       short b,
	       SDL_Renderer *render
	     )
{
	SDL_Rect rect;
	rect.w = width;
	rect.h = height;
	rect.x = x;
	rect.y = y;
	SDL_RenderDrawRect(render,&rect);
	SDL_SetRenderDrawColor(render,r,g,b,1);
	SDL_RenderFillRect(render,&rect);
}

