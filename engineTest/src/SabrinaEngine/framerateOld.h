#ifndef _FRAMERATEOLD_H
#define _FRAMERATEOLD_H

#include <iostream>
#include <SDL2/SDL.h>

struct Ticks
{
	Uint32 start, pause;
	bool started, paused;
};

struct FrameRate
{
	Ticks fpsTimer, capTimer;
	short targetFrameRate,ticksPerFrame,countedFrames;
	float avgFPS,timeStep;
};

// System Clock Ticks 
void initTicks(Ticks*);
void startTicking(Ticks*);
void stopTicking(Ticks*);
void pauseTicking(Ticks*);
void unPauseTicks(Ticks*);
Uint32 getTicks(Ticks*);

// Capping FPS
short calTicksPerFrame(short&);
float calCorrectFPS(FrameRate*);
void calEndFPS(FrameRate*);

#endif
