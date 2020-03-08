#include "SDL.h"
#include "Game.h"
#include "Globals.h"
#include <iostream>

Uint32 startTime=SDL_GetTicks(),finalTime = 0;
double dt = 0;
enum STATES {
	CREATION,INIT,UPDATE,FINISH,EXIT
};

Game* gGame = nullptr; //We declare game object as pointer because it uses dynamic memory

int main(int argc, char* argv[]) {
	
	int failure = EXIT_FAILURE;
	STATES state = CREATION;
	
	while (state != EXIT) {
		
		switch (state) {
		case CREATION:
		{
			LOG("Creating the game......");
			gGame = new Game(); //creating game object.
			state = INIT; //changing state of the main to initialization
		}break;
		case INIT:
		{LOG("Initializing game......");
		if (gGame->Init() == false) {
			LOG("Exit from game with some errors......");
			state = EXIT; //changing state to exit the game
		}
		else {
			state = UPDATE;
			LOG("Entering Game Update.......");
		}
		}break;
		case UPDATE:
		{
			int update_result = gGame->Update();
			if (update_result == UPDATE_ERROR) {
				LOG("Exiting Game Update with some errors......");
				state = EXIT;
			}
			else if (update_result == UPDATE_STOP) {
				state = FINISH;
			}
		}break;
		case FINISH:
		{
			LOG("Cleaning Game......");
			if (gGame->CleanUp() == false)//if the cleanup gives an error the game is finished with errors
			{
				LOG("Game CleanUp returning with some errors -----");
			}
			else {
				failure = EXIT_SUCCESS;
				state = EXIT;
			}
		}break;
		}
	}
	delete gGame;
	LOG("Game finished, hope you liked it.\n");
	return failure;
}