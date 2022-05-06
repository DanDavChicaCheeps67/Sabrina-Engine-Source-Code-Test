#include "sprites.h"

void renderSpriteFrame(Sprite* source, SDL_Renderer* ren)
{
	short rowPos = source->spriteHeight / source->rowNumToRender,
	      columPos = source->spriteWidth / source->numOfSpritesInRow
	      ;

	SDL_Rect frame;
	frame.w = source->spriteWidth;
	frame.h = source->spriteHeight;
	frame.x = source->frameInRow * columPos;
	frame.y = rowPos * source->rowNumToRender;

	source->pos.x = xPos;
	source->pox.y = yPos;

	SDL_RenderCopyEx(ren,
			source->spriteSheet,
			&frame,
			source->pos,
			source->angle,
			NULL,
			source->flip,

			);
}

void renderBackForeToScreen(BackForeGround* source, SDL_Renderer* ren)
{
	source->pos.x = xPos;
	source->pos.y = yPos;
	SDL_RenderCopyEx(ren,
			 source->image,
			 NULL,
			 source->pos,
			 source->angle,
			 NULL,
			 source->flip
			);
}

bool lockTexture(SDL_Texture* source, short &pit, void &pix)
{
	bool worked = false;

	if ( pix != NULL)
		printf("Already Locked\n");
	else
	{
		if (SDL_LockTexture(source, NULL, &pix, &pit) == 0)
			worked = true;
		else
			printf("SDL_Error: %s\n", SDL_GetError());
	}

	return worked;
}

bool unlockTexture(SDL_Texture* source, short &pit, void &pix)
{
	bool worked = false;
	
	if (pix != NULL)
	{
		SDL_UnlockTexture(source);
		pix = NULL;
		pit = 0;
		worked = true;
	} else
		printf("Already Unlocked\n");

	return worked;
}

void alphaColorRemoval( SDL_Window *win,
			SDL_Texture *source,
			Uint8 *aColor,
			short &pit,
			void &pix,
			short &width,
			short &height
		      )
{
	if (lockTexture(source, pit, pix) != false)
	{
		Uint32 form = SDL_GetWindowPixelFormat(win);
		Uint32 *pixels = (Uint32*)pix;
		short pixCount = (pit/4) * height;
		SDL_PixelFormat* map = SDL_AllocFormat(form);

		Uint32 key = SDL_MapRGB( map,aColor[0],aColor[1],aColor[2]);
		Uint32 transparent = SDL_MapRGBA(map, 0xFF, 0xFF, 0xFF, 0x00);

		for (int i = 0; i < pixCount; i++)
		{
			if (pixels[i] == key)
				pixels[i] = transparent;
		}
		
		bool checkUnlock = false;
		
		do 
		{
			checkUnlock = unlockTexture(source, pit, pix);

		} while(checkUnlock != true);
		
		SDL_FreeFormat(map);
	} else
		print("UNABLE TO LOCK\n");
}

void changeColor( SDL_Window* win,
		  SDL_Texture* source, 
		  Uint8* level,
		  Uint8* target, 
		  bool flag, 
		  short &pit, 
		  void &pix, 
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
		
			bool checkUnlock = false;
		
			do 
			{
				checkUnlock = unlockTexture(source, pit, pix);

			} while(checkUnlock != true);
		
			SDL_FreeFormat(map);
		} else
			print("UNABLE TO LOCK\n");

	}

}

void alphaBlend(SDL_Texture* source, Uint8* level)
{
	SDL_SetTextureAlphaMod(source,level);
}

void freeSprite(Sprite* source)
{
	SDL_DestroyTexture(source->spriteSheet);
}

void freBackFore(BackForeGround* source)
{
	SDL_DestroyTexture(source->image);
}
