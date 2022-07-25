#include "input.h"

bool initInput()
{
	
	if (SDL_InitSubSystem( SDL_INIT_EVENTS|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC|SDL_INIT_GAMECONTROLLER ) != 0)
	{
		printf("SDL ERROR: %s\n",SDL_GetError());
		return false;
	}
	else{
		printf("MIZUARHA\n");
		return true;
	}
}

void initInputKeys(Input* source)
{
	// Keyboard Init
	const Uint8* states = SDL_GetKeyboardState(&source->board.numOfKeys);
	source->board.keyState = (bool*)malloc(source->board.numOfKeys * sizeof(bool));
	source->board.prevKeyState = (bool*)malloc(source->board.numOfKeys * sizeof(bool));
	for (short i = 0; i < source->board.numOfKeys; i++)
	{
		source->board.keyState[i] = states[i];
		source->board.prevKeyState[i] = false;
	}
	// Mouse Init
	SDL_GetMouseState(&source->mouse.xPos, &source->mouse.yPos);
	source->mouse.prevXPos = 0;
	source->mouse.prevYPos = 0;
	source->mouse.keys = (bool*)malloc(4 * sizeof(bool));
	source->mouse.prevKeys = (bool*)malloc(4 * sizeof(bool));
	for (int i = 0; i <= 3; i++)
	{
		source->mouse.keys[i] = SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(i);
		source->mouse.prevKeys[i] = false;
	}

	// Joystick Init
	source->numOfJoysticks = SDL_NumJoysticks();
	printf("Num of Joysticks: %d\n", source->numOfJoysticks);
	if (source->numOfJoysticks > 0)
	{
		printf("Starting to Allocate\n");
		source->pad = (struct Gamepad *)malloc(source->numOfJoysticks * sizeof(struct Gamepad));
		printf("Pads Address: %p\n",&source->pad);
		if (source->pad == NULL)
			printf("PADS NULL\n");
		else
		{
			printf("Allocated Mem for PADS\n");

			for (short i = 0; i < source->numOfJoysticks; i++)
			{
				source->pad[i].joypad = SDL_JoystickOpen(i);
				printf("OPEN PAD # %d\n", i);
					source->pad[i].name = SDL_JoystickName(source->pad[i].joypad);
					printf("PUT NAME IN C STRING\n");
					printf("Name of Pad: %s\n",source->pad[i].name);

					// Button Initalization 
					source->pad[i].numOfButtons = SDL_JoystickNumButtons(source->pad[i].joypad);
					if (source->pad[i].numOfButtons > 0)
					{
						source->pad[i].buttonState = (int*)malloc(source->pad[i].numOfButtons * sizeof(int));
						source->pad[i].prevButtonState = (int*)malloc(source->pad[i].numOfButtons * sizeof(int));
						for (short h = 0; h < source->pad[i].numOfButtons; h++)
						{
							source->pad[i].buttonState[h] = SDL_JoystickGetButton(source->pad[i].joypad,h);
							source->pad[i].prevButtonState[h] = 0;
						}
					}

					// D-PAD / HAT Init
					source->pad[i].numOfHats = SDL_JoystickNumHats(source->pad[i].joypad);
					if (source->pad[i].numOfHats > 0)
					{
						printf("NUM OF HATS: %d\n", source->pad[i].numOfHats);
						source->pad[i].hatPressed = (int*)malloc(source->pad[i].numOfHats * sizeof(int));
						source->pad[i].prevHatPressed = (int*)malloc(source->pad[i].numOfHats * sizeof(int));
						for (short h = 0; h < source->pad[i].numOfHats; h++)
						{
							source->pad[i].hatPressed[h] = SDL_JoystickGetHat(source->pad[i].joypad,h);
							source->pad[i].prevHatPressed[h] = 0;
						}
					}

					// Axis Init
					source->pad[i].numOfAxes = SDL_JoystickNumAxes(source->pad[i].joypad);
					if (source->pad[i].numOfAxes > 0)
					{
						source->pad[i].axis = (int*)malloc(source->pad[i].numOfAxes * sizeof(int));
						source->pad[i].prevAxis = (int*)malloc(source->pad[i].numOfAxes * sizeof(int));
						for (short h = 0; h < source->pad[i].numOfAxes; h++)
						{
							source->pad[i].axis[h] = SDL_JoystickGetAxis(source->pad[i].joypad,h);
							source->pad[i].prevAxis[h] = 0;
						}
					}

					// Balls Init
					source->pad[i].numOfBalls = SDL_JoystickNumBalls(source->pad[i].joypad);
					if (source->pad[i].numOfBalls > 0)
					{
						for (short h = 0; h < source->pad[i].numOfBalls; h++)
						{
							if ( SDL_JoystickGetBall(source->pad[i].joypad,h,
										 &source->pad[i].deltaX,
										 &source->pad[i].deltaY
										) 
							     < 0
							   )
								printf("SDL Error: %s\n", SDL_GetError());
						}
					}

					source->pad[i].index = i+1;
					source->pad[i].deadZone = 8000;
					source->pad[i].pluggedIn = true;
			}
		}
	}
}

void checkWindowEvent(SDL_Event &e, SDL_Window *win)
{
	switch(e.window.event)
	{
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_HideWindow(win); break;
	}
}
bool checkCloseWindow(Window* win)
{
	//SDL_Event check;
	bool close = false;

	while (SDL_PollEvent(&win->check))
	{
		switch(win->check.type)
		{
			case SDL_WINDOWEVENT:
				checkWindowEvent(win->check, win->window);
				break;
			case SDL_QUIT:
				close = true; break;
		}
	}
	return close;
}

void killInput(Input* source)
{
	// Free Keyboard
	free(source->board.keyState);
	free(source->board.prevKeyState);
	
	// Free Mouse
	printf("Mouse-Keys Address: %p\n", &source->mouse.keys);
	free(source->mouse.keys);
	printf("Mouse-Keys Address: %p\n", &source->mouse.keys);

	printf("Mouse-prevKeys Address: %p\n", &source->mouse.prevKeys);
	free(source->mouse.prevKeys);
	printf("Mouse-prevKeys Address: %p\n", &source->mouse.prevKeys);

	// Free Joypads
	if (source->numOfJoysticks > 0)
	{
		// Free Joypad
		SDL_JoystickClose(source->pad->joypad);

		// Free Buttons
		free(source->pad->buttonState);
		free(source->pad->prevButtonState);
		
		// Free Hats
		free(source->pad->hatPressed);
		free(source->pad->prevHatPressed);

		// Free axis
		free(source->pad->axis);
		free(source->pad->prevAxis);
		free(source->pad);
	}
}

void freeInput()
{
	SDL_QuitSubSystem( SDL_INIT_EVENTS|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC|SDL_INIT_GAMECONTROLLER );
}

void updateInput(Input* source)
{
	// Update Keyboard
	const Uint8* states = SDL_GetKeyboardState(&source->board.numOfKeys);
	for (short i = 0; i < source->board.numOfKeys; i++)
	{
		source->board.prevKeyState[i] = source->board.keyState[i];
		source->board.keyState[i] = states[i];
	}

	// Update Mouse
	source->mouse.prevXPos = source->mouse.xPos;
	source->mouse.prevYPos = source->mouse.yPos;
	SDL_GetMouseState(&source->mouse.xPos, &source->mouse.yPos);
	for (int i = 0; i <= 3; i++)
	{
		source->mouse.prevKeys[i] = source->mouse.keys[i];
		source->mouse.keys[i] = SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(i);
	}

	SDL_JoystickUpdate();
	for (int i = 0; i < source->numOfJoysticks; i++)
	{
		for (short h = 0; h < source->pad[i].numOfButtons; h++)
		{
			source->pad[i].prevButtonState[h] = source->pad[i].buttonState[h];
			source->pad[i].buttonState[h] = SDL_JoystickGetButton(source->pad[i].joypad,h);
		}	

		for (short h = 0; h < source->pad[i].numOfAxes; h++)
		{
			source->pad[i].prevAxis[h] = source->pad[i].axis[h];
			source->pad[i].axis[h] = SDL_JoystickGetAxis(source->pad[i].joypad,h);
		}

		for (short h = 0; h < source->pad[i].numOfBalls; h++)
		{
			SDL_JoystickGetBall( source->pad[i].joypad, 
					     h,
					     &source->pad[i].deltaX,
					     &source->pad[i].deltaY
					   );
		}

		for (short h = 0; h < source->pad[i].numOfHats; h++)
		{
			//printf("HAT VALE: %d\n",source->pad[i].hatState[h]);
			source->pad[i].prevHatPressed[h] = source->pad[i].hatPressed[h];
			source->pad[i].hatPressed[h] = SDL_JoystickGetHat(source->pad[i].joypad,h);

		}
	}
}

bool keyboardDown(Keyboard* source, int pressed)
{
	bool isDown;
	if (pressed < 0 || pressed > source->numOfKeys)
		isDown = false;
	else
		isDown = (source->keyState[pressed]);

	return isDown;
}

bool keyboardHit(Keyboard *source,int pressed)
{
	if (pressed < 0 || pressed > source->numOfKeys)
		return false;
	else
	{
		if (source->keyState[pressed] == true)
		{
			printf("KeyState[%d] Value: %d\n",pressed,source->keyState[pressed]);
			if (source->prevKeyState[pressed] != true)
			{
				printf("prevKeyState[%d] Value: %d\n",pressed,source->prevKeyState[pressed]);
				return true;
			}
		}
		return false;
	}
}

bool keyboardUp(Keyboard *source,int pressed)
{
	bool isUp;
	if (pressed < 0 || pressed > source->numOfKeys)
		isUp = false;
	else
		isUp = (source->prevKeyState[pressed] && !source->keyState[pressed]);

	return isUp;
}

bool mouseDown(Mouse* source, int pressed)
{
	bool isDown;
	if (pressed < 0 || pressed > 3)
		isDown = false;
	else
		isDown = (source->keys[pressed]);
	
	return isDown;	
}

bool mouseHit(Mouse* source, int pressed)
{
	bool isHit;
	
	if ((pressed < 0) || (pressed > 3))
		isHit = true;
	else
		isHit = (source->keys[pressed] && !source->prevKeys[pressed]);

	return isHit;
}

bool mouseUp(Mouse* source, int pressed)
{
	bool isUp;
	
	if ((pressed < 0) || (pressed > 3))
		isUp = false;
	else
		isUp = (source->prevKeys[pressed] && !source->keys[pressed]);

	return isUp;
}

void setMousePos(Mouse* source, SDL_Window* win)
{
	SDL_WarpMouseInWindow(win,source->xPos,source->yPos);
}

void hidCursor(Mouse* source)
{
	if (source->hide == true)
		SDL_ShowCursor(SDL_DISABLE);
	else
		SDL_ShowCursor(SDL_ENABLE);
}

// Gamepad button
bool gamepadButtonDown(Gamepad* source,int pressed)
{
	bool isDown;
	if (pressed < 0 || pressed > source->numOfButtons)
		isDown = false;
	else
		isDown = (source->buttonState[pressed]);

	return isDown;
}

bool gamepadButtonHit(Gamepad* source,int pressed)
{
	bool isHit;
	if (pressed < 0 || pressed > source->numOfButtons)
	{
		printf("IS HIT FALSE\n");
		isHit = false;
	}
	else
	{
		if (source->buttonState[pressed] > 0)
		{
			if (source->prevButtonState[pressed] == 0)
			{
				isHit = true;
				printf("IS HIT TRUE\n");
			}
		}
	}
	return isHit;
}

bool gamepadButtonUp(Gamepad* source,int pressed)
{
	bool isUp;
	if (pressed < 0 || pressed > source->numOfButtons)
		isUp = false;
	else
		isUp = (source->prevButtonState[pressed] && !source->buttonState[pressed]);

	return isUp;
}
// Gamepad Hat

