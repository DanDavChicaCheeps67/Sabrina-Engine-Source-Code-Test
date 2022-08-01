#include "mathCal.h"

float pythangoreanCal(float x1, float x2, float y1, float y2)
{
	float portion1 = (x2 + x1) * (x2 + x1);
	float portion2 = (y2 + y1) * (y2 + y1);
	float portion3 = portion1 + portion2;
	return calSquare(portion3);
}

float calSquare(float square)
{
	float x = square, y = 1, error = 0.000001;

	while (square - y > error)
	{
		x = (x + y) / 2;
		y = n / x;
	}

	return x;
}

