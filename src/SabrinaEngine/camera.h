#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <SDL2/SDL.h>

#include "collision.h"
#include "graphics.h"


class Camera
{
	private:
		SDL_Rect pos;
		short xPos,yPos,width,height;
		collisionBox area;
		bool check,renderBox;

	public:
		Camera(short,short,short,short);
		
		bool checkInitalized();
		void updatePosition(short,short);
		void turnOnRenderBox();
		void turnOffRenderBox();
		
		~Camera();

} 


#endif 
