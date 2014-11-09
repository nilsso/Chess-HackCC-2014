#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#endif

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

	//sendMail();

	getchar();
	return 0;
}
