#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <time.h>
#include <SDL2/SDL.h>
#include "graphics.h"

/*
 //Define Input Values
 Controller D-PAD 
#define D-PAD-UP 1
#define D-PAD-DOWN 4
#define D-PAD-RIGHT 2
#define D-PAD-LEFT 8
#define D-PAD-UPRIGHT 3
#define D-PAD-DOWNRIGHT 6
#define D-PAD-DOWNLEFT 12
#define D-PAD-UPLEFT 9
// Controller Switch Pro
*/

struct Keyboard
{
	bool *keyState, *prevKeyState;
	int numOfKeys, keyPressed, prevKeyPressed;
};

struct Mouse
{
	bool *keys, *prevKeys, hide;
	int xPos, yPos, keyPressed;
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
void mouseDown(Mouse*);
bool keyboardHit(Keyboard*,int);
bool mouseHit(Mouse*);
bool keyboardUp(Keyboard*,int);
bool mouseUp(Mouse*);
void setMousePos(Mouse*, SDL_Window*);
void hidCursor(Mouse*);

bool gamepadButtonDown(Gamepad*,int);
bool gamepadButtonHit(Gamepad*,int);
bool gamepadButtonUp(Gamepad*,int);

#endif
