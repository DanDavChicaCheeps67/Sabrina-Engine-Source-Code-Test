#include "framerateOld.h"

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
	source->paused = false;
	source->start = SDL_GetTicks();
	printf("StartTicks : %d\n",source->start);
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

Uint32 getTicks(Ticks* source)
{
	Uint32 time = 0;
	Uint32 ticking = SDL_GetTicks();
	printf("ticking (getTicks): %d\n",ticking);
	printf("Source->start (getTicks): %d\n",source->start);
	Uint32 sub = ticking - source->start;
	printf("Value of Sub (getTicks): %d\n",sub);

	if (source->started == true)
	{
		if (source->paused == true)
		{
			printf("PAUSED\n");
			printf("source->pause (getTicks): %d\n", source->pause);
			time = source->pause;
		}	       
		else
		{
			printf("TIME = SUB\n");
			time = sub;
		}
	} else
		printf("TICKS NOT STARTED\n");
	
	printf("time: %d\n",time);

	return time;
}

short calTicksPerFrame(short& fps)
{
	short screenTick = 1000 / fps;
	return screenTick;
}

float calCorrectFPS(FrameRate* source)
{
	printf("Initial avgFPS (calCorrectFPS): %d\n", source->avgFPS);
	float maxFrameNum = 2000000;
	Uint32 time = getTicks(&source->fpsTimer);
	printf("Returned time (calCorrectFPS): %d\n", time);
	float timer = time / 1000.f;
	printf("timer (calCorrectFPS): %d\n", timer);
	short counted = source->countedFrames;
	printf("Counted Frames (calCorrectFPS): %d\n", counted);
	float avgFPS = counted / timer;
	printf("avgFPS (calCorrectFPS): %d\n", avgFPS);

	if (avgFPS > maxFrameNum)
	{
		printf("avgFPS RESTARTED\n");
		avgFPS = 0;
	}

	return avgFPS;
}

void calEndFPS(FrameRate* source)
{
	Uint32 frameTicks = getTicks(&source->capTimer);
	printf("FrameTicks(calENDFPS): %d\n",frameTicks);
	short tPF = source->ticksPerFrame;
	printf("Ticks Per Frame (calEndFPS): %d\n",tPF);
	Uint32 delay = tPF - frameTicks;
	if (frameTicks < tPF)
	{
		printf("Delay (calEndFPS): %d\n", delay);
		SDL_Delay(delay);
	}
}

