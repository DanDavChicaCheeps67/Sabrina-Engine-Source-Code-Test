#include "collision.h"

void initCollisionBox(collisionBox *source, float xPos, float yPos, int w, int h)
{
	source->xPos = xPos;
	source->yPos = yPos;
	source->width = w;
	source->height = h;

	source->left = source->xPos;
	source->right = source->xPos + source->width;
	source->top = source->yPos;
	source->bottom = source->yPos + source->height;
}

void addColor(collisionBox *source, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	source->color[0] = r;
	source->color[1] = g;
	source->color[2] = b;
	source->color[3] = a;
}

void toSDLRect(collisionBox *source)
{
	source->Box.w = source->width;
	source->Box.h = source->height;
	source->Box.x = source->xPos;
	source->Box.y = source->yPos;
}

bool checkCollision(collisionBox *boxOne, collisionBox *boxTwo)
{
	boxOne->left = boxOne->xPos;
	boxOne->right = boxOne->xPos + boxOne->width;
	boxOne->top = boxOne->yPos;
	boxOne->bottom = boxOne->yPos + boxOne->height;
	
	boxTwo->left = boxTwo->xPos;
	boxTwo->right = boxTwo->xPos + boxTwo->width;
	boxTwo->top = boxTwo->yPos;
	boxTwo->bottom = boxTwo->yPos + boxTwo->height;

	if (boxOne->bottom <= boxTwo->top)
		return false;
	else if (boxOne->top >= boxTwo->bottom)
		return false;
	else if (boxOne->right <= boxTwo->left)
		return false;
	else if (boxOne->left >= boxTwo->right)
		return false;
	else
		return true;
}

void initSensor(collisionSensor *source, float x, float y)
{
	source->xPos = x;
	source->yPos = y;
}

void toSDLPoint(collisionSensor *source)
{
	source->point.x = source->xPos;
	source->point.y = source->yPos;
}
