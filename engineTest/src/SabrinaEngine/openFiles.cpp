#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "openFiles.h"

void openSettingsFile(std::string &location, short *flag)
{
	std::fstream Settings;
	Settings.open(location, std::ios::in);

	std::string get;
	if (Settings.good())
	{
			// Read Settings file for rendering flags
			short i = 0;
			while (!Settings.eof())
			{
				std::getline(Settings,get,'\n');
				flag[i] = short(atoi(get.c_str()));
				i++;
			}
	} else
		printf("Can't Open File\n");
		// Make default flag Zero
		flag = 0;

	Settings.close();
}

void openSaveFile(std::string location)
{

}

SDL_Texture* loadImageManual( SDL_Window* win, 
		        SDL_Renderer* ren, 
			std::string &location, 
			void **pixels, 
			short &pitch, 
			float &width, 
			float &height
		      )
{
	SDL_Texture* newTex = NULL;
	SDL_Surface* loaded = SDL_LoadBMP(location.c_str());
	Uint32 pixelFormat = SDL_GetWindowPixelFormat(win);

	if (loaded != NULL)
	{
		SDL_Surface* formatted = SDL_ConvertSurfaceFormat( loaded,
								  pixelFormat,
								  0
								);
		printf("Formatted Surface\n");

		if (formatted != NULL)
		{
			newTex = SDL_CreateTexture( ren,
				       		    pixelFormat,
						    SDL_TEXTUREACCESS_STREAMING,
						    formatted->w,
						    formatted->h
						  );
			printf("Created new Texture\n");

			if ( newTex != NULL)
			{
				SDL_LockTexture( newTex,
						 NULL,
						 pixels,
						 (int *)&pitch
					       );
				memcpy( *pixels,
					formatted->pixels,
					(formatted->pitch * formatted->h)
				      );
				printf("Pixel address: %s\n",pixels);
				
				SDL_UnlockTexture(newTex);
				*pixels = NULL;
				printf("Pixel Address: %s\n",pixels);
				width = formatted->w;
				height = formatted->h;
				printf("PIXELS ARE NULL NOW\n");
			}
			else
				printf("SDL_Error: %s\n", SDL_GetError());
		}
		else 
			printf("SDL_Error: %s\n", SDL_GetError());

		SDL_FreeSurface(formatted);

	} else
		printf("SDL_Error: %s\n",SDL_GetError());

	SDL_FreeSurface(loaded);
	
	return newTex;
}

Mix_Music* loadMusic(std::string &location)
{
	Mix_Music* loaded = Mix_LoadMUS(location.c_str());
	return loaded;
}

Mix_Chunk* loadSoundEffect(std::string &location)
{
	Mix_Chunk* loaded = Mix_LoadWAV(location.c_str());
	return loaded;
}
