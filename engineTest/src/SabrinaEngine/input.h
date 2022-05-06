#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <time.h>
#include <SDL2/SDL.h>
#include "graphics.h"

struct Controller
{
	SDL_GameController *pad;
	bool *keys, *prevKeys, *buttons, *prevButtons;
	short numKeys, numButtons;
	float deadzone;

};

// init SDL Events, Joystick, Gamecontroller. and Haptic-Feedback
bool initInput();

// Check if Window needs to be closed
bool checkCloseWindow(Window*);
void checkWindowEvent(SDL_Event&, SDL_Window*);

// Gamepad Input
/*
bool initGamepad(Controller*,short&);
void updateGamepad(Controller*);
void freeController(Controller*);
*/
//Keyboard Input
bool initKeyBoard();
void freeInput();

#endif
