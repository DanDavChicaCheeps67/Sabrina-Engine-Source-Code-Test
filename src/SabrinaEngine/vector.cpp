#include "vector.h"

void initVector(Vector* source, short x, short y)
{
	source->xPos = x;
	source->yPos = y;
}

void calVectorDistance(Vector *source, short x, short y)
{
	source->distance = pythagoreanCal(source->xPos, x, source->yPos, y);
}

