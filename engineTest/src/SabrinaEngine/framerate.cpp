#include "framerate.h"

void initTicks(Ticks* source)
{
	source->start = 0;
	source->pause = 0;	
	source->started = false;
	source->paused = false;
}

void startTicking(Ticks* source)
{
	source->started = true;
	source->started = false;
	source->start = SDL_GetTicks();
	source->pause = 0;
}

void stopTicking(Ticks* source)
{
	source->started = false;
	source->paused = false;
	source->start = 0;
	source->pause = 0;
}

void pauseTicking(Ticks* source)
{
	if ( (source->started != false) && (source->paused == false) )
	{
		source->paused = true;
		source->pause = SDL_GetTicks() - source->start;
		source->start = 0;
	}
}

void unPauseTicking(Ticks* source)
{
	Uint32 pauseTicks = source->pause;
	if ( (source->started != false) && (source->pause == true) )
	{
		source->pause = false;
		source->start = SDL_GetTicks() - pauseTicks;
		source->pause = 0;
	}	
}

short getTicks(Ticks* source)
{
	short time = 0;

	if (source->started != false)
	{
		if (source->paused != false)
		       time = source->pause;	
		else
			time = (short)SDL_GetTicks() - (short)source->start;
	} else
		printf("TICKS NOT STARTED\n");

	return time;
}

short calTickPerFrame(short fps)
{
	short screenTick = 1000 / fps;
	return screenTick;
}

void calCorrectFPS(FrameRate* source)
{
	float maxFrameNum = 2000000;
	float timer = getTicks(&source->fpsTimer) / 1000.f;
	source->avgFPS = source->countedFrames / timer;
	
	if (source->avgFPS > maxFrameNum)
		source->avgFPS = 0;
}

void calEndFPS(FrameRate* source)
{
	short frameTicks = getTicks(&source->capTimer);

	if (frameTicks < source->ticksPerFrame)
		SDL_Delay(source->ticksPerFrame - frameTicks);
}

