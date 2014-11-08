#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <vector>
#include "time.h"


#include <iostream>


class PrisonChess
{
public:

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	const int CHESS_SQUARE_WIDTH = 100;
	const int CHESS_SQUARE_HEIGHT = 100;

	const int ROOK_1 = 0;
	const int KNIGHT_1 = 1;
	const int BISHOP_1 = 2;
	const int QUEEN = 3;
	const int KING = 4;
	const int BISHOP_2 = 5;
	const int KNIGHT_2 = 6;
	const int ROOK_2 = 7;

	const int A = 20;
	const int B = 120;
	const int C = 220;
	const int D = 320;
	const int E = 420;
	const int F = 520;
	const int G = 620;
	const int H = 720;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	SDL_Renderer* gRenderer;

	TTF_Font *gFont;

	class LTexture
	{
	public:

		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font *gFont);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		SDL_Texture* mTexture;

		//The window renderer



	private:
		//The actual hardware texture


		//Image dimensions
		int mWidth;
		int mHeight;
	};

	//Main loop flag
	bool quit = false;


	//Event handler
	SDL_Event e;



	//Scene textures


	static PrisonChess& getInstance();
	~PrisonChess();


	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	void start();


	//
	void handleEvent(SDL_Event& e);

	void mainLoop();

	void setUpChessBoard(int yPos);

	void renderChessBoard();

	void renderChessPieces();


	std::vector<SDL_Rect> bSquares;


	LTexture gBlackBishop;
	LTexture gBlackKing;
	LTexture gBlackKnight;
	LTexture gBlackPawn;
	LTexture gBlackQueen;
	LTexture gBlackRook;

	LTexture gWhiteBishop;
	LTexture gWhiteKing;
	LTexture gWhiteKnight;
	LTexture gWhitePawn;
	LTexture gWhiteQueen;
	LTexture gWhiteRook;

	struct ChessPiece
	{
		int xPos;
		int yPos;
	};

	

	ChessPiece bRook1;

	std::vector<ChessPiece*>wPieces;
	std::vector<ChessPiece*>bPieces;

	LTexture topGridNumberTextTexture;
	LTexture grid1Text;
	LTexture grid2Text;
	LTexture grid3Text;
	LTexture grid4Text;
	LTexture grid5Text;
	LTexture grid6Text;
	LTexture grid7Text;
	LTexture grid8Text;


	void setupGridNumbers();

	void parseInput(bool turn);
	bool whiteTurn = true;
	bool playGame = false;

	bool saveScreenshotBMP(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer);
};

