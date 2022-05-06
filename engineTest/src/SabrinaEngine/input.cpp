#include "input.h"

bool initInput()
{
	bool worked = false;
	
	if (SDL_InitSubSystem( SDL_INIT_EVENTS|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC|SDL_INIT_GAMECONTROLLER ) != 0)
		printf("SDL ERROR: %s\n",SDL_GetError());
	else{
		printf("MIZUARHA\n");
		worked = true;
	}

	return worked;
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
	bool close = false;
	SDL_Event check;

	while (SDL_PollEvent(&check))
	{
		switch(check.type)
		{
			case SDL_WINDOWEVENT:
				checkWindowEvent(check, win->window);
				break;
			case SDL_QUIT:
				close = true; break;
		}
	}
	return close;
}

/*
bool initGamePad(Controller* con, short &i)
{
	bool worked = false;
	if (SDL_IsGameController(i))
	{
		con->pad = SDL_GameControllerOpen(i);
		if (con->pad)
		{
			worked = true;
			Uint8* gamepad = SDL_GameControllerGetButton(con->pad,NULL);
	
			con->buttons = new bool[con->numButtons];
			con->prevButtons = new bool[con->numButtons];

			for (int i = 0; i < con->numButtons; i++)
			{
				con->buttons[i] = gamepad[i];
				con->prevButtons[i] = false;
			}
		}
		else
			printf("SDL ERROR: %s\n",SDL_GetError());
	}

	return worked;
}

void updateController(Controller* con)
{
	Uint8* gamepad = SDL_GameControllerGetButton(con->pad,NULL);
	for (int i = 0; i < con->numButtons; i++)
	{
		con->prevButtons[i] = con->buttons[i];
		con->buttons[i] = gamepad[i];
	}
}

void freeController(Controller* con)
{
	SDL_GameControllerClose(con->pad);
	con->pad = NULL;
	delete[] con->buttons;
	delete[] con->prevButtons;
}
*/

void freeInput()
{
	SDL_QuitSubSystem( SDL_INIT_EVENTS|SDL_INIT_JOYSTICK|SDL_INIT_HAPTIC|SDL_INIT_GAMECONTROLLER );
}
