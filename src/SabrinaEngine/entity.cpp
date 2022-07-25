#include "entity.h"

Entity :: Entity( Window *win,
		 std::string spriteSheetLocation,
		 bool manualLoading,
		 int alphaOne,
		 int alphaTwo,
		 int alphaThree,
		 int spriteWidth,
		 int spriteHeight,
		 int spriteXPos,
		 int spriteYPos,
		 short numOfBoxes,
		 int collisionBoxWidth,
		 int collisionBoxHeight,
		 int collisionBoxXPos,
		 int collisionBoxYPos,
		 bool haveSensors
	       )
{
	bool initSpriteCheck = initSprite( &sprite,
		    			   win,
		    			   spriteSheetLocation,
		    			   manualLoading,
		    			   alphaOne,
		    			   alphaTwo,
		    			   alphaThree,
		    			   spriteWidth,
		    			   spriteHeight,
		    			   spriteXPos,
		    			   spriteYPos
		  			 );
	if (initSpriteCheck)
	{
		calOrigin(&sprite);
		
		boxCollision = (collisionBox*)malloc(numOfCollisionBoxes * sizeof(collisionBox));
		boxCollisionDistanceX = (float*)malloc(numOfCollisionBoxes * sizeof(float));
		boxCollisionDistanceY = (float*)malloc(numOfCollisionBoxes * sizeof(float));

		for (short i = 0; i < numOfCollisionBoxes; i++)
		{	
			initCollisionBox( &boxCollision[i],
					  collisionBoxXPos,
					  collisionBoxYPos,
					  collisionBoxWidth,
					  collisionBoxHeight
					);
			boxCollisionDistanceX[i] = boxCollision[i].xPos - sprite.xPos;
			boxCollisionDistanceY[i] = boxCollision[i].yPos - sprite.yPos;
		}
		
		numOfCollisionBoxes = numOfBoxes;

		if (haveSensors)
		{
			initSensor( &sensors[0],
			            boxCollision[0].xPos,
				    boxCollision[0].yPos
				  );
			
			initSensor( &sensors[1],
				    boxCollision[0].xPos + boxCollision[0].width,
				    boxCollision[0].yPos
				  );

			initSensor( &sensors[2],
				    boxCollision[0].xPos,
				    boxCollision[0].yPos + boxCollision[0].height
				  );

			initSensor( &sensors[3],
				    boxCollision[0].xPos + boxCollision[0].width,
				    boxCollision[0].yPos + boxCollision[0].height
				  );
		}else
			printf("No Sensors Init\n");
		check = true;
	}else
	{
		printf("Failed to Init Sprite\n");
		check = false;
	}
}

void Entity :: initEntityAnimation(int firstFrame, int maxFrame, int frameDelay, int frameWidth, int frameHeight)
{
	initAnimation( &sprite,
		       firstFrame,
		       maxFrame,
		       frameDelay,
		       frameWidth,
		       frameHeight
		     );
}

void Entity :: updateEntityAnimation()
{
	updateSpriteAnimation(&sprite);
}

void Entity :: changeEntitySpriteColor(Uint8 r, Uint8 g, Uint8 b, SDL_Window *win)
{
	sprite.colorChange[0] = r;
	sprite.colorChange[1] = g;
	sprite.colorChange[2] = b;

	changeColorSprite( &sprite,
			   win,
			   &sprite.pixels
			 );
}

bool Entity :: setEntityBlendMode(bool turnOn, short mode)
{
	SDL_BlendMode setMode;

	switch (mode)
	{
		case 1: setMode = SDL_BLENDMODE_BLEND; break;
		case 2: setMode = SDL_BLENDMODE_ADD; break;
		case 3: setMode = SDL_BLENDMODE_MOD; break;
		default: setMode = SDL_BLENDMODE_NONE; break;
	}

	printf("BLEND MODE SET: %d\n",mode);

	return setBlendingModeSprite(&sprite,turnOn,setMode);
}

void Entity :: alphaBlendEntity(Uint8 level)
{
	sprite.alphaLevels = level;
	alphaBlendSprite(&sprite);
}

void Entity :: renderEntity(SDL_Renderer *ren, bool flip)
{
	sprite.flip = flip;
	renderSpriteFrame(&sprite,ren);
}

void Entity :: moveEntity(float xPos, float yPos)
{
	sprite.xPos = xPos;
	sprite.yPos = yPos;
	
	for (short i = 0; i < numOfCollisionBoxes; i++)
	{
		boxCollision[i].xPos = sprite.xPos + boxCollisionDistanceX[i];
		boxCollision[i].yPos = sprite.yPos + boxCollisionDistanceY[i];
	}

	sensors[0].xPos = boxCollision[0].xPos;
	sensors[0].yPos = boxCollision[0].yPos;
	sensors[1].xPos = boxCollision[0].xPos + boxCollision[0].width;
	sensors[1].yPos = boxCollision[0].yPos;
	sensors[2].xPos = boxCollision[0].xPos;
	sensors[2].yPos = boxCollision[0].yPos + boxCollision[0].height;
	sensors[3].xPos = boxCollision[0].xPos + boxCollision[0].width;
	sensors[3].yPos = boxCollision[0].yPos + boxCollision[0].height;
}

void Entity :: renderEntityCollisionBox(SDL_Renderer *ren, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	for (short i = 0; i < numOfCollisionBoxes; i++)
	{
		toSDLRect(&boxCollision[i]);
		boxCollision[i].color[0] = r;
		boxCollision[i].color[1] = g;
		boxCollision[i].color[2] = b;
		boxCollision[i].color[3] = a;

		drawOwnRect( &boxCollision[i].Box,
		   	     ren,
			     r,
		             g,
		             b,
		             a	     
			   );
	}
}

Entity :: ~Entity()
{
	free(boxCollision);
	free(boxCollisionDistanceX);
	free(boxCollisionDistanceY);
	freeSprite(&sprite);
}

