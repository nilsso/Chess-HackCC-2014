#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "time.h"

#include "PrisonChess.h"

int main(int argc, char* args[])
{
	PrisonChess game = PrisonChess::getInstance();
	game.start();
	game.mainLoop();

	return 0;
}
