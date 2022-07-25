#include "graphics.h"

bool initGraphics()
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL ERROR: %s\n", SDL_GetError());
		return false;
	}
	else
		return true;
}

bool windowSetup( Window* source,
		  short width,
		  short height,
		  std::string title,
		  Uint32 winFlag,
		  Uint32 renFlag,
		  int renderIndex,
		  short scaleFlag,
		  bool renderToBackbuffer,
		  Uint8 backgroundColorR,
		  Uint8 backgroundColorG,
		  Uint8 backgroundColorB,
		  Uint8 backgroundColorA,
		  short fps
		)
{
	source->width = width;
	source->height = height;
	source->title = title;
	source->winFlags = winFlag;
	source->scaleFlag = scaleFlag;
	source->renderIndex = renderIndex;

	source->renderToBackbuffer = renderToBackbuffer;

	source->backgroundColor[0] = backgroundColorR;
	source->backgroundColor[1] = backgroundColorG;
	source->backgroundColor[2] = backgroundColorB;
	source->backgroundColor[3] = backgroundColorA;
	
	source->bufferFlip = SDL_FLIP_NONE;

	source->window = SDL_CreateWindow( source->title.c_str(),
			                   SDL_WINDOWPOS_UNDEFINED,
					   SDL_WINDOWPOS_UNDEFINED,
					   source->width,
					   source->height,
					   source->winFlags
			                 );

		if (source->window != NULL)
		{
			source->render = SDL_CreateRenderer( source->window,
					                     source->renderIndex,
							     source->renFlags
					                   );
			if (source->render == NULL)
			{
				printf("SDL Error: %s\n",SDL_GetError);
				return false;
			}
			else 
			{
				if (source->renderToBackbuffer != false)
				{
					source->backbuffer = SDL_CreateTexture( source->render,
										SDL_PIXELFORMAT_RGBA8888,	
										SDL_TEXTUREACCESS_TARGET,
										source->width,
										source->height
									      );
					if (source->backbuffer == NULL)
						printf("SDL ERROR: %s\n",SDL_GetError());
				}
				SDL_RenderSetLogicalSize(source->render,source->width,source->height);
				return true;
			}
		}
		else
		{
			printf("SDL Error: %s\n",SDL_GetError());
			return false;
		}

}

void clearGraphics(Window *win, SDL_Renderer *ren)
{
	if (win->renderToBackbuffer != false)
		SDL_SetRenderTarget(ren, win->backbuffer);

	SDL_SetRenderDrawColor( ren,
			        win->backgroundColor[0],
				win->backgroundColor[1],
				win->backgroundColor[2],
				1
			      );
	
	
	SDL_RenderClear(ren);	
}

void updateRender(Window *win, SDL_Renderer *ren)
{
	if (win->renderToBackbuffer != false)
	{
		printf("BACKBUFFER RENDER\n");
		// Restart Target
		SDL_SetRenderTarget(ren, NULL);

		// Rendering BackBuffer
		SDL_RenderCopy( ren,
				win->backbuffer,
				NULL,
				NULL
		      	      );
	}

	SDL_RenderPresent(win->render);
}

void destroyWindow(Window *source)
{
	SDL_DestroyRenderer(source->render);
	if (source->render == NULL)
	{
		SDL_DestroyWindow(source->window);
		if (source->window != NULL)
			printf("SDL ERROR: %s\n",SDL_GetError());
	} else
		printf("SDL Error: %s\n",SDL_GetError());
}

void clearGraphics()
{	
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void changeBufferColor(SDL_Renderer *ren, Uint8 *colorChange)
{
	SDL_SetRenderDrawColor( ren,
			        colorChange[0],
				colorChange[1],
				colorChange[2],
				colorChange[3]
			      );
	SDL_RenderClear(ren);
}

void drawPixel( short x,
		short y,
		short r,
		short g,
		short b,
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

void drawOwnRect(SDL_Rect *source, SDL_Renderer *ren, int r, int g, int b, int a)
{
	SDL_RenderDrawRect(ren,source);
	SDL_SetRenderDrawColor(ren,r,g,b,a);
	SDL_RenderFillRect(ren,source);
}

void drawCircle(short x0, short y0, short radius, short r, short g, short b, SDL_Renderer *ren)
{
	short x = radius - 1,
	      y = 0,
	      dx = 1,
	      dy = 1,
	      err = dx - (radius << 1)
	;

	while (x >= y)
	{
		drawPixel(x0 + x, y0 + y, r, g, b, ren);
		drawPixel(x0 + y, y0 + x, r, g, b, ren);
		drawPixel(x0 - y, y0 + x, r, g, b, ren);
		drawPixel(x0 - x, y0 + y, r, g, b, ren);
		drawPixel(x0 - x, y0 - y, r, g, b, ren);
		drawPixel(x0 - y, y0 - x, r, g, b, ren);
		drawPixel(x0 + y, y0 - x, r, g, b, ren);
		drawPixel(x0 + x, y0 - y, r, g, b, ren);

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0)
		{
			x--;
			dx += 2;
			err += dx = (radius << 1);
		}
	}
}

