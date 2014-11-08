#include "PrisonChess.h"

PrisonChess::~PrisonChess()
{
	//endwin();
}

PrisonChess& PrisonChess::getInstance()
{
	static PrisonChess instance;
	return instance;
}



bool PrisonChess::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("21st Century Prison Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool PrisonChess::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if (!gBlackBishop.loadFromFile("rsc/black_bishop.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackKing.loadFromFile("rsc/black_king.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackKnight.loadFromFile("rsc/black_knight.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackPawn.loadFromFile("rsc/black_pawn.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackQueen.loadFromFile("rsc/black_queen.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackRook.loadFromFile("rsc/black_rook.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}



	if (!gWhiteBishop.loadFromFile("rsc/white_bishop.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteKing.loadFromFile("rsc/white_king.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteKnight.loadFromFile("rsc/white_knight.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhitePawn.loadFromFile("rsc/white_pawn.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteQueen.loadFromFile("rsc/white_queen.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteRook.loadFromFile("rsc/white_rook.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("SlimJoe.ttf", 18);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{

		setupGridNumbers();
	}

	return success;
}

void PrisonChess::close()
{


	//Free loaded images

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



void PrisonChess::start()
{

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{


		}
	}
}


void PrisonChess::handleEvent(SDL_Event& e)
{

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			//bRook1.yPos -= 100;
			break;
		case SDLK_DOWN:
			//bRook1.yPos += 100;
			break;

		case SDLK_LEFT:
			//bRook1.xPos -= 100;
			break;
		case SDLK_RIGHT:
			//bRook1.xPos += 100;
			break;

		case SDLK_0:
			playGame = true;
			break;

		case SDLK_s:
			saveScreenshotBMP("test.png", gWindow, gRenderer);
			break;
		}
	}
}


bool PrisonChess::saveScreenshotBMP(std::string filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = NULL;
	infoSurface = SDL_GetWindowSurface(SDLWindow);
	if (infoSurface == NULL) {
		std::cerr << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
	}
	else {
		unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (pixels == 0) {
			std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n";
			return false;
		}
		else {
			if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
				pixels = NULL;
				return false;
			}
			else {
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
				if (saveSurface == NULL) {
					std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
					return false;
				}
				SDL_SaveBMP(saveSurface, filepath.c_str());
				SDL_FreeSurface(saveSurface);
				saveSurface = NULL;
			}
			delete[] pixels;
		}
		SDL_FreeSurface(infoSurface);
		infoSurface = NULL;
	}
	return true;
}


PrisonChess::LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

PrisonChess::LTexture::~LTexture()
{
	//Deallocate
	free();
}


int PrisonChess::LTexture::getWidth()
{
	return mWidth;
}

int PrisonChess::LTexture::getHeight()
{
	return mHeight;
}

void PrisonChess::LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void PrisonChess::LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void PrisonChess::LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void PrisonChess::LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

bool PrisonChess::LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont)
{

	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

bool PrisonChess::LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


void PrisonChess::LTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void PrisonChess::setUpChessBoard(int yPos)
{
	bSquares.clear();

	SDL_Rect k;
	k.w = 100;
	k.h = 100;
	k.y = yPos;
	for (int i = 0; i < 8; i++)
	{
		k.x = i * 100;

		bSquares.push_back(k);
	}
}

void PrisonChess::renderChessBoard()
{

	for (int j = 0; j < 8; j++)
	{
		setUpChessBoard(j * 100);

		for (int i = 0; i < 8; i++)
		{
			if (j % 2 == 0)
			{
				if (i % 2 == 0)
				{
					SDL_SetRenderDrawColor(gRenderer, 200, 150, 60, 255);
					SDL_RenderFillRect(gRenderer, &bSquares[i]);
				}
				else
				{
					SDL_SetRenderDrawColor(gRenderer, 90, 60, 30, 255);
					SDL_RenderFillRect(gRenderer, &bSquares[i]);
				}
			}
			else
			{
				if (i % 2 == 1)
				{
					SDL_SetRenderDrawColor(gRenderer, 200, 150, 60, 255);
					SDL_RenderFillRect(gRenderer, &bSquares[i]);
				}
				else
				{
					SDL_SetRenderDrawColor(gRenderer, 90, 60, 30, 255);
					SDL_RenderFillRect(gRenderer, &bSquares[i]);
				}
			}
		}
	}
}

void PrisonChess::parseInput(bool turn)
{
	std::string moveStr;

	if (turn == true)
	{
		printf("\n WHITE, please enter your move: \n");
	}
	else
	{
		printf("\n BLACK, please enter your move: \n");
	}

	std::getline(std::cin, moveStr);

	char test = ' ';
	char test2 = ' ';
	char test3 = ' ';

	if (moveStr.length() > 0)
	{
		test = moveStr.at(0);
	}
	else
	{
		printf("\ninvalid input, try again\n");
		parseInput(whiteTurn);
	}

	if (moveStr.length() > 1)
	{
		test2 = moveStr.at(moveStr.length() - 1);
	}

	if (moveStr.length() > 2)
	{
		test3 = moveStr.at(moveStr.length() - 2);
	}

	int piece = 0;
	int pieceX = 0;
	int pieceY = 0;

	switch (test)
	{
		case 'R':
			test = moveStr.at(1);

			if (test == '1')
			{
				piece = ROOK_1;
			}
			else
			{
				piece = ROOK_2;
			}
		break;

		case 'K':
			test = moveStr.at(1);

			if (test == '1')
			{
				piece = KNIGHT_1;
			}
			else if (test == '2')
			{
				piece = KNIGHT_2;
			}
			else
			{
				piece = KING;
			}

		break;

		case 'B':
			test = moveStr.at(1);

			if (test == '1')
			{
				piece = BISHOP_1;
			}
			else
			{
				piece = BISHOP_2;
			}

		break;

		case 'Q':
			piece = QUEEN;

		break;

		case 'T':
			playGame = false;
			break;

		default:
			printf("\ninvalid input, try again\n");
			parseInput(whiteTurn);
			break;
	}

	if (test == 'T')
	{
		return;
	}

	switch (test2)
	{
	case '1':
		pieceY = A;
		break;

	case '2':
		pieceY = B;
		break;

	case '3':
		pieceY = C;
		break;

	case '4':
		pieceY = D;
		break;

	case '5':
		pieceY = E;
		break;

	case '6':
		pieceY = F;
		break;

	case '7':
		pieceY = G;
		break;

	case '8':
		pieceY = H;
		break;

	default:
		printf("\ninvalid input, try again\n");
		parseInput(whiteTurn);
		break;

	}

	switch (test3)
	{
	case 'A':
		pieceX = A;
		break;

	case 'B':
		pieceX = B;
		break;

	case 'C':
		pieceX = C;
		break;

	case 'D':
		pieceX = D;
		break;

	case 'E':
		pieceX = E;
		break;

	case 'F':
		pieceX = F;
		break;

	case 'G':
		pieceX = G;
		break;

	case 'H':
		pieceX = H;
		break;

	default:
		printf("\ninvalid input, try again\n");
		parseInput(whiteTurn);
		break;

	}

	if (turn)
	{
		wPieces[piece]->xPos = pieceX;
		wPieces[piece]->yPos = pieceY;

	}
	else
	{
		bPieces[piece]->xPos = pieceX;
		bPieces[piece]->yPos = pieceY;

	}




}

void PrisonChess::setupGridNumbers()
{
	SDL_Color textColor = { 0, 0, 0 };
	if (!topGridNumberTextTexture.loadFromRenderedText("A         B          C          D         E          F          G         H", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}

	if (!grid1Text.loadFromRenderedText("1", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
	if (!grid2Text.loadFromRenderedText("2", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
	if (!grid3Text.loadFromRenderedText("3", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
	if (!grid4Text.loadFromRenderedText("4", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
	if (!grid5Text.loadFromRenderedText("5", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
	if (!grid6Text.loadFromRenderedText("6", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
	if (!grid7Text.loadFromRenderedText("7", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
	if (!grid8Text.loadFromRenderedText("8", textColor, gRenderer, gFont))
	{
		printf("Failed to render text texture!\n");

	}
}

void PrisonChess::renderChessPieces()
{
	gBlackRook.render(gRenderer,    bPieces[ROOK_1]->xPos,    bPieces[ROOK_1]->yPos);
	gBlackKnight.render(gRenderer,  bPieces[KNIGHT_1]->xPos,  bPieces[KNIGHT_1]->yPos);
	gBlackBishop.render(gRenderer,  bPieces[BISHOP_1]->xPos,  bPieces[BISHOP_1]->yPos);
	gBlackQueen.render(gRenderer,   bPieces[QUEEN]->xPos,     bPieces[QUEEN]->yPos);

	gBlackKing.render(gRenderer,	bPieces[KING]->xPos,      bPieces[KING]->yPos);
	gBlackBishop.render(gRenderer,  bPieces[BISHOP_2]->xPos,  bPieces[BISHOP_2]->yPos);
	gBlackKnight.render(gRenderer,  bPieces[KNIGHT_2]->xPos,  bPieces[KNIGHT_2]->yPos);
	gBlackRook.render(gRenderer,    bPieces[ROOK_2]->xPos,    bPieces[ROOK_2]->yPos);

	gWhiteRook.render(gRenderer,    wPieces[ROOK_1]->xPos,    wPieces[ROOK_1]->yPos);
	gWhiteKnight.render(gRenderer,  wPieces[KNIGHT_1]->xPos,  wPieces[KNIGHT_1]->yPos);
	gWhiteBishop.render(gRenderer,  wPieces[BISHOP_1]->xPos,  wPieces[BISHOP_1]->yPos);
	gWhiteQueen.render(gRenderer,   wPieces[QUEEN]->xPos,     wPieces[QUEEN]->yPos);

	gWhiteKing.render(gRenderer,    wPieces[KING]->xPos,      wPieces[KING]->yPos);
	gWhiteBishop.render(gRenderer,  wPieces[BISHOP_2]->xPos,  wPieces[BISHOP_2]->yPos);
	gWhiteKnight.render(gRenderer,  wPieces[KNIGHT_2]->xPos,  wPieces[KNIGHT_2]->yPos);
	gWhiteRook.render(gRenderer,    wPieces[ROOK_2]->xPos,    wPieces[ROOK_2]->yPos);


	for (int i = 0; i < 8; i++)
	{
		gBlackPawn.render(gRenderer, 100*i + 20, 120);
	}

	for (int i = 0; i < 8; i++)
	{
		gWhitePawn.render(gRenderer, 100 * i + 20, 620);
	}
}

void PrisonChess::mainLoop()
{
	printf("PRESS 0 TO START GAME\n");
	printf("ENTER T TO TERMINATE GAME\n");
	printf("PRESS S TO SAVE SCREENSHOT\n");

	for (int i = 0; i < 8; i++)
	{
		bPieces.push_back(new ChessPiece);
		bPieces[i]->xPos = 20+(i*100);
		bPieces[i]->yPos = A;

		wPieces.push_back(new ChessPiece);
		wPieces[i]->xPos = 20 + (i * 100);
		wPieces[i]->yPos = H;
	}


	//While application is running
	while(!quit)
	{

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			handleEvent(e);

		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);


		renderChessBoard();

		renderChessPieces();

		topGridNumberTextTexture.render(gRenderer, 5, 5);

		grid1Text.render(gRenderer, 5, 80);
		grid2Text.render(gRenderer, 5, 180);
		grid3Text.render(gRenderer, 5, 280);
		grid4Text.render(gRenderer, 5, 380);
		grid5Text.render(gRenderer, 5, 480);
		grid6Text.render(gRenderer, 5, 580);
		grid7Text.render(gRenderer, 5, 680);
		grid8Text.render(gRenderer, 5, 780);

		//Update screen
		SDL_RenderPresent(gRenderer);

		if (playGame == true)
		{


			if (whiteTurn)
			{
				parseInput(whiteTurn);
				whiteTurn = false;
			}
			else
			{
				parseInput(whiteTurn);
				whiteTurn = true;
			}

		}
	}




	//SDL_WaitThread(threadID, NULL);

	//Free resources and close SDL
	close();

	getchar();
}
