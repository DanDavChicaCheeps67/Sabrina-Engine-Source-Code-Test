#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <time.h>
#include <SDL2/SDL.h>
#include "graphics.h"

struct Keyboard
{
	bool *keyState, *prevKeyState;
	int numOfKeys, keyPressed, prevKeyPressed;
};

struct Mouse
{
	bool *keys, *prevKeys, hide;
	int xPos, prevXPos, yPos, prevYPos, keyPressed;
};

struct Gamepad
{
	SDL_Joystick *joypad;
	int *buttonState, *prevButtonState, *hatState, *hatPressed, *prevHatPressed;
	const char *name;
	bool pluggedIn;
	int *axis, *prevAxis;
	int deltaX, deltaY;
	int numOfButtons, numOfBalls, numOfAxes, numOfHats, index, state, deadZone;
};

struct Input
{
	Keyboard board;
	Mouse mouse;
	struct Gamepad *pad;
	bool joySticksPluggedIn;
	short numOfJoysticks;
	SDL_Event check;
};

// init SDL Events, Joystick, Gamecontroller. and Haptic-Feedback
bool initInput();
void initInputKeys(Input*);
// Check if Window needs to be closed
bool checkCloseWindow(Window*);
void checkWindowEvent(SDL_Event&, SDL_Window*);
// Free Input
void killInput(Input*);
void freeInput();
// Input Handling
void updateInput(Input*);
bool keyboardDown(Keyboard*,int);
bool mouseDown(Mouse*,int);
bool keyboardHit(Keyboard*,int);
bool mouseHit(Mouse*,int);
bool keyboardUp(Keyboard*,int);
bool mouseUp(Mouse*,int);
void setMousePos(Mouse*, SDL_Window*);
void hidCursor(Mouse*);

bool gamepadButtonDown(Gamepad*,int);
bool gamepadButtonHit(Gamepad*,int);
bool gamepadButtonUp(Gamepad*,int);

#endif
