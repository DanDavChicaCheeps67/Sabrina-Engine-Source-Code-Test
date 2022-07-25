#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include <SDL2/SDL.h>
#include <iostream>

typedef struct FrameRate
{
	short FPS, frameCounter;
	float frameDelay;
	Uint32 startTime, passedTime, delay;
}FrameRate;

void initFrameRate(FrameRate*,short);
void updateFrameRateFirst(FrameRate*);
void updateFrameRateSecond(FrameRate*);
bool resetCounter(FrameRate*);

#endif
