#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_ttf.h>
#endif






#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

class PrisonChess
{
public:

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 800;

	const int CHESS_SQUARE_WIDTH = SCREEN_WIDTH / 8;
	const int CHESS_SQUARE_HEIGHT = SCREEN_HEIGHT / 8;

	const int ROOK_1 = 0;
	const int KNIGHT_1 = 1;
	const int BISHOP_1 = 2;
	const int QUEEN = 3;
	const int KING = 4;
	const int BISHOP_2 = 5;
	const int KNIGHT_2 = 6;
	const int ROOK_2 = 7;

	const int A = CHESS_SQUARE_WIDTH * 0 + CHESS_SQUARE_WIDTH / 5;
	const int B = CHESS_SQUARE_WIDTH * 1 + CHESS_SQUARE_WIDTH / 5;
	const int C = CHESS_SQUARE_WIDTH * 2 + CHESS_SQUARE_WIDTH / 5;
	const int D = CHESS_SQUARE_WIDTH * 3 + CHESS_SQUARE_WIDTH / 5;
	const int E = CHESS_SQUARE_WIDTH * 4 + CHESS_SQUARE_WIDTH / 5;
	const int F = CHESS_SQUARE_WIDTH * 5 + CHESS_SQUARE_WIDTH / 5;
	const int G = CHESS_SQUARE_WIDTH * 6 + CHESS_SQUARE_WIDTH / 5;
	const int H = CHESS_SQUARE_WIDTH * 7 + CHESS_SQUARE_WIDTH / 5;


	std::string assetPath;

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

		int pieceType;

		char colLocation;
		char rowLocation;
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

	bool checkIfValidMove(ChessPiece* p, int newX, int newY);
};

