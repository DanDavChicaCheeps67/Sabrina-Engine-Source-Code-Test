#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>
#include <SDL2/SDL.h>
#include <tmx>
#include "camera.h"
#include "collision.h"
#include "sprites.h"
#include "graphics.h"

// Sensor collision for tile
/*
 * Subtract the detected tile's Pos with the Sensor's Pos which results in the index used.
 * then used the index to find the tile's unique hight array. Then subtract the the y value of
 * the sensor with the height in the array index.
 */

class TileMap
{
	private:
		SDL_Texture *map;
		std::string tileLocation, mapLocation;
		short tileWidth, tileHeight,mapWidth,mapHeight;
	public:
		TileMap(std::string);
		bool checkCollision();
		void renderMap();
		~TileMap();

};


#endif
