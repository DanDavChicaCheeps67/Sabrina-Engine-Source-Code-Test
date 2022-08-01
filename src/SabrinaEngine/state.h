#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <SDL2/SDL.h>

class State
{
	private:
		bool check
		std::string name;
	public:
		State();
		State(std::string);
		bool checkState();
		void update();
		void freeState();
		std::string *getName();
		~State();	
};


#endif
