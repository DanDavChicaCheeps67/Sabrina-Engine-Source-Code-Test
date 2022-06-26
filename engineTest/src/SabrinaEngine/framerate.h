#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include <SDL2/SDL.h>
#include <iostream>

struct FrameRate
{
	short FPS, frameCounter;
	float frameDelay;
	Uint32 startTime, passedTime, delay;
};

float calFrameDelay(short&);
bool resetCounter(FrameRate*);
void delayFrame(FrameRate*);
void updateStartTime(FrameRate*);
void updatePassedTime(FrameRate*);

#endif
