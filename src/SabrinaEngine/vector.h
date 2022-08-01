#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "mathCal.h"

typedef struct Vector
{
	short xPos, yPos;
	float distance;
} Vector;

void initVector(Vector*,short,short);
void calVectorDistance(Vector*,short,short);


#endif 
