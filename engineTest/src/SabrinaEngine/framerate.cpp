#include "framerate.h"

float calFrameDelay(short &fps)
{
	float delay = 1000 / fps;
	//printf("delay: %f\n", delay);
	return delay;
}

bool resetCounter(FrameRate *source)
{
	bool restarted = false;
	if(source->frameCounter > source->frameDelay)
	{
		source->frameCounter = 0;
		restarted = true;
	}
	return restarted;
}

void updateStartTime(FrameRate *source)
{
	source->startTime = SDL_GetTicks();
	//printf("StartTime: %d\n", source->startTime);
}

void updatePassedTime(FrameRate *source)
{
	//printf("Inital passedTime: %f\n", source->passedTime);
	source->passedTime = SDL_GetTicks() - source->startTime;
	//printf("Frame Time: %f\n", source->passedTime);
}

void delayFrame(FrameRate *source)
{
	if (source->passedTime < source->frameDelay)
	{
		source->delay = source->frameDelay - source->passedTime;	
		//printf("DELAY\n");
		SDL_Delay(source->delay);
	}
}

