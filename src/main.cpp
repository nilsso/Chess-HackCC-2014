#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "time.h"
#include <SDL_thread.h>



#include "PrisonChess.h"


int main(int argc, char* args[])
{

	PrisonChess game = PrisonChess::getInstance();
	game.start();
	game.mainLoop();

	return 0;
}