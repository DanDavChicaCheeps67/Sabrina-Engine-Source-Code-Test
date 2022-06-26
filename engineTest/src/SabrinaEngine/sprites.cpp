#include "sprites.h"

bool initSprite(Sprite* source,
	       	Window* win,
		std::string local, 
		bool manual, 
		int alphaOne, 
		int alphaTwo, 
		int alphaThree,
	       	int spriteWidth,
		int spriteHeight,	
		int xPos, 
		int yPos)
{
	bool initWorked = false, checkLoadSprite = false;
	
	source->spriteSheetLocation = local;
	source->alphaColor[0] = alphaOne;
	source->alphaColor[1] = alphaTwo;
	source->alphaColor[2] = alphaThree;

	if (manual != false)
	{
		if (loadSpriteSheetManual(source,win,&source->pixels) != false)
		{
			if (alphaColorRemovalSprites(source,win->window,&source->pixels) == false)
				printf("ALPHA COLOR REMOVAL FAIL\n");
			else
				checkLoadSprite = true;
		}
	}
	else
	{
		if (loadSpriteSheet(source,win->render) != false)
			checkLoadSprite = true;
		else
			printf("Auto Load Failed\n");
	}

	if (checkLoadSprite != false)
	{
		source->spriteWidth = spriteWidth;
		source->spriteHeight = spriteHeight;
		initWorked = true;
	}
	else
		printf("CANT LOAD SPRITE\n");

	return initWorked;
}

void initAnimation(Sprite* source, int firstFrame, int maxFrame, int frameDelay, int frameWidth, int frameHeight)
{
	source->firstFrame = firstFrame;
	source->maxFrames = maxFrame;
	source->delay = frameDelay;
	source->frameWidth = frameWidth;
	source->frameHeight = frameHeight;
	source->delayCounter = 0;
}

bool loadSpriteSheet(Sprite* source, SDL_Renderer* ren)
{
	bool worked = false;
	SDL_Texture *newTex = NULL;
	SDL_Surface *loaded = NULL;

	printf("SpriteSheet location: %s\n", source->spriteSheetLocation.c_str());
	loaded = SDL_LoadBMP(source->spriteSheetLocation.c_str());
	printf("Surface Loaded Status: %p\n", loaded);

		Uint32 key = SDL_MapRGB( loaded->format,
					 source->alphaColor[0],
					 source->alphaColor[1],
					 source->alphaColor[2]
				       );
		short checkKeySucess = SDL_SetColorKey( loaded,
							SDL_TRUE,
							key
						      );

		if (checkKeySucess != 0)
			printf("SDL ERROR: %s\n", SDL_GetError());
		else
		{
			newTex = SDL_CreateTextureFromSurface(ren,loaded);
			source->spriteSheet = newTex;
			Uint32 form = 0;
			int acc = 0, wi = 0, hi =0;
			short checkQuery = SDL_QueryTexture( source->spriteSheet,
							     &form,
							     &acc,
							     &wi,
							     &hi
							   );
			if(checkQuery != 0)
				printf("SDL Error: %s\n", SDL_GetError());
			else
			{
				// transfer local values to Sprite Struct
				source->format = form;
				source->textAccess = acc;
				source->sheetWidth = wi;
				printf("Sheet Width: %d\n",source->sheetWidth);
				source->sheetHeight = hi;
				printf("Sheet Height: %d\n",source->sheetHeight);
				worked = true;
			}
		}

	return worked;
}

bool loadSpriteSheetManual(Sprite* source, Window* win, void **pixels)
{
	bool worked = false;	
	//printf("Pixel Address: %s\n", *pixels);

	SDL_Surface *loaded = SDL_LoadBMP(source->spriteSheetLocation.c_str());
	Uint32 pixelFormat = SDL_GetWindowPixelFormat(win->window);

	if (loaded != NULL)
	{
		SDL_Surface* formatted = SDL_ConvertSurfaceFormat( loaded,
								   pixelFormat,
								   0
								 );

		if (formatted != NULL)
		{
			source->spriteSheet = SDL_CreateTexture( win->render,
						    pixelFormat,
						    SDL_TEXTUREACCESS_STREAMING,
						    formatted->w,
						    formatted->h
						  );

			if (source->spriteSheet != NULL)
			{
				SDL_LockTexture( source->spriteSheet,
						 NULL,
						 pixels,
						 &source->pitch
					       );
				memcpy( *pixels,
					formatted->pixels,
					(formatted->pitch * formatted->h)
				      );
				
				//printf("Pixels Adrdress: %s\n", *pixels);
				//printf("Source->Pixel Address: %s\n", source->pixels);
				SDL_UnlockTexture(source->spriteSheet);
				*pixels = NULL;
				//printf("Pixels Address: %s\n",*pixels);
				if (*pixels == NULL)
				{
					source->sheetWidth = formatted->w;
					source->sheetHeight = formatted->h;
					worked = true;
				} else
						printf("PIXELS NOT NULL\n");
			} else
				printf("SDL_Error: %s\n",SDL_GetError());
			SDL_FreeSurface(formatted);
		} else
			printf("SDL_Error: %s\n",SDL_GetError());

	} else
		printf("SDL_Error: %s\n",SDL_GetError());

	SDL_FreeSurface(loaded);

	return worked;
}

void updateSprite(Sprite *source)
{
	source->delayCounter += 1;

	if (source->delayCounter > source->delay)
	{
		source->delayCounter = 0;
		source->frameNum++;
	}

	if (source->frameNum > source->maxFrames)
		source->frameNum = source->firstFrame;
}

void renderSpriteFrame(Sprite* source, SDL_Renderer* ren)
{
	// Location on screen	
	SDL_Rect position;
	position.x = source->xPos;
	position.y = source->yPos;
	position.w = source->spriteWidth;
	position.h = source->spriteHeight;

	//printf("Sprite Y-pos: %d\n",position.y);
	//printf("Sprite X-pos: %d\n",position.x);
	//printf("Sheet Width: %d\n",source->sheetWidth);
	//printf("Sheet Height: %d\n",source->sheetHeight);
	short columns = source->sheetWidth / source->frameWidth;
	//printf("Columns: %d\n",columns);

	SDL_Rect frame;
	frame.y = (source->frameNum / columns) * source->frameHeight;
	//printf("Frame Y: %d\n",frame.y);
	frame.x = (source->frameNum % columns) * source->frameWidth;
	//printf("Frame X: %d\n",frame.x);
	frame.w = source->frameWidth;
	//printf("Frame Width: %d\n",frame.w);
	frame.h = source->frameHeight;
	//printf("Frame Height: %d\n",frame.h);
	
	if (source->flip == true)
		source->fliped = SDL_FLIP_HORIZONTAL;
	else if (source->flip == false)
		source->fliped = SDL_FLIP_NONE;

	short check = SDL_RenderCopyEx(ren,
				     	source->spriteSheet,
			 	     	&frame,
			   	     	&position,
				     	source->angle,
				     	NULL,
				     	source->fliped
				      );
	 if (check != 0)
		 printf("SDL_ERROR: %s\n", SDL_GetError());
	 else
		 printf("SHOWING ON SCREEN\n");
	 
}

void renderBackForeToScreen(BackForeGround* source, SDL_Renderer* ren)
{
	source->pos.x = source->xPos;
	source->pos.y = source->yPos;
	SDL_RenderCopyEx(ren,
			 source->image,
			 NULL,
			 &source->pos,
			 source->angle,
			 NULL,
			 source->flip
			);
}

bool lockTexture(SDL_Texture* source, int &pit, void **pix)
{
	bool worked = false;

	if (*pix != NULL)
		printf("TEXTURE IS ALREADY LOCKED\n");
	else
	{
		if (SDL_LockTexture(source, NULL, pix, &pit) == 0)
			worked = true;
		else
			printf("SDL_Error: %s\n", SDL_GetError());

	}		
	
	return worked;
}

bool unlockTexture(SDL_Texture* source, short &pit, void **pix)
{
	bool worked = false;
	
	if (*pix != NULL)
	{
		SDL_UnlockTexture(source);
		*pix = NULL;
		pit = 0;
		worked = true;
	} else
		printf("Already Unlocked\n");

	return worked;
}

bool alphaColorRemovalSprites(Sprite* source, SDL_Window* win, void **pixels)
{
	bool worked = false;	

	//printf("Pixels Status: %s\n",*pixels);

	if (*pixels != NULL)
		printf("SPRITESHEET PIXELS NOT NULL\n");
	else
	{
		short lockCheck = SDL_LockTexture( source->spriteSheet,
					   	    NULL,
					            pixels,
						    &source->pitch
			                 	 );	
		if (lockCheck != 0)
			printf("UNABLE TO LOCK");
		else
		{
			Uint32 form = SDL_GetWindowPixelFormat(win);
			SDL_PixelFormat *map = SDL_AllocFormat(form);
			Uint32 *pix = (Uint32 *)*pixels;
			int pixCount = (source->pitch / 4) * source->sheetHeight;

			Uint32 key = SDL_MapRGBA( map,
						 source->alphaColor[0],
						 source->alphaColor[1],
						 source->alphaColor[2],
						 source->alphaColor[3]
						 );
			
			Uint32 transparent = SDL_MapRGBA( map, 
							  0xFF, 
							  0xFF, 
							  0xFF,
							  0x00 
							);

			for (short i = 0; i < pixCount; i++)
			{
				//printf("VALUE OF KEY: %d\n", key);
				//printf("VALUE OF PIXEL: %d\n", pix);
				if (pix[i] == key)
				{
					pix[i] = transparent;
					//printf("CHANGING COLOR\n");
				}
			}

			if (*pixels != NULL)
			{
				SDL_UnlockTexture(source->spriteSheet);
				*pixels = NULL;
				
				if (*pixels == NULL)
				{
					source->pitch = 0;
					worked = true;
				} else
					printf("PIXELS NOT NULL");

			}
			if (source->pixels == NULL)
				printf("WAS UNLOCKED\n");

			SDL_FreeFormat(map);
		}
	}

	return worked;
}
void changeColor( SDL_Window* win,
		  SDL_Texture* source, 
		  Uint8* level,
		  Uint8* target, 
		  bool flag, 
		  int &pit, 
		  void **pix, 
		  short &width, 
		  short &height
		 )
{
	// Use SDL_SetTextureColorMod to change color
	if (flag != false)
		SDL_SetTextureColorMod(source,level[0],level[1],level[2]);
	else 
	{
		if (lockTexture(source, pit, pix) != false)
		{
			Uint32 form = SDL_GetWindowPixelFormat(win);
			Uint32 *pixels = (Uint32*)pix;
			short pixCount = (pit/4) * height;
			SDL_PixelFormat* map = SDL_AllocFormat(form);

			Uint32 key = SDL_MapRGB( map,target[0],target[1],target[2]);
			Uint32 change = SDL_MapRGB(map, level[0], level[1], level[2]);

			for (int i = 0; i < pixCount; i++)
			{
				if (pixels[i] == key)
					pixels[i] = change;
			}
		
			SDL_UnlockTexture(source);
		
			SDL_FreeFormat(map);
		} else
			printf("UNABLE TO LOCK\n");

	}

}

void alphaBlend(SDL_Texture* source, Uint8* level)
{
	SDL_SetTextureAlphaMod(source,*level);
}

void freeSprite(Sprite* source)
{
	SDL_DestroyTexture(source->spriteSheet);
}

void freBackFore(BackForeGround* source)
{
	SDL_DestroyTexture(source->image);
}
