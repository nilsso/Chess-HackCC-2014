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


void PrisonChess::sendMail(std::string mailContents)
{
		::CoInitialize(NULL);

		EASendMailObjLib::IMailPtr oSmtp = NULL;
		oSmtp.CreateInstance("EASendMailObj.Mail");
		oSmtp->LicenseCode = ("TryIt");

		// Set your sender email address
		oSmtp->FromAddr = ("PrisonChessHackCC@yahoo.com");

		// Add recipient email address
		oSmtp->AddRecipientEx(("blizzard1445@gmail.com"), 0);

		// Set email subject
		oSmtp->Subject = ("PrisonChess: Your opponent has made his move!");

		// Set email body
		oSmtp->BodyText = ((char*)mailContents.c_str());

		//Add embedded image and return the unique identifier of the attachment
		_bstr_t cid = oSmtp->AddInline("test.png");
		if (cid.length() == 0)
		{
			printf("failed add embedded image with error: %s"),
				(const TCHAR*)oSmtp->GetLastErrDescription();
		}

		//Set HTML body format
		oSmtp->BodyFormat = 1;

		//use the cid as link in the body text
		oSmtp->BodyText = _bstr_t("<html><body>Hello, this is a  embedded <img src=\"cid:") + cid
			+ _bstr_t("\" > picture.</body><html>");

		// Your SMTP server address
		oSmtp->ServerAddr = ("localhost");

		// User and password for ESMTP authentication, if your server doesn't 
		// require User authentication, please remove the following codes.
		oSmtp->UserName = ("573a70c398b6463fd21d0911ef82b91b");
		oSmtp->Password = ("41f53f546115e7c7dfdafd1be2c0e86e");


		// If your smtp server requires SSL connection, please add this line
		//oSmtp->SSL_init();

		printf(("Start to send email ...\r\n"));

		if (oSmtp->SendMail() == 0)
		{
			printf(("email was sent successfully!\r\n"));
		}
		else
		{
			printf(("failed to send email with the following error: %s\r\n"),
				(const TCHAR*)oSmtp->GetLastErrDescription());
		}

		if (oSmtp != NULL)
			oSmtp.Release();

}

using namespace EAGetMailObjLib;
void PrisonChess::retreiveMail()
{


}

bool PrisonChess::init()
{
#ifdef _WIN32
	assetPath = "repo/assets/";
#else
	assetPath = "assets/";
#endif

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
		gWindow = SDL_CreateWindow("21st Century Prison Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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
	if (!gBlackBishop.loadFromFile(assetPath + "black_bishop.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackKing.loadFromFile(assetPath + "black_king.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackKnight.loadFromFile(assetPath + "black_knight.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackPawn.loadFromFile(assetPath + "black_pawn.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackQueen.loadFromFile(assetPath + "black_queen.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gBlackRook.loadFromFile(assetPath + "black_rook.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}



	if (!gWhiteBishop.loadFromFile(assetPath + "white_bishop.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteKing.loadFromFile(assetPath + "white_king.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteKnight.loadFromFile(assetPath + "white_knight.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhitePawn.loadFromFile(assetPath + "white_pawn.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteQueen.loadFromFile(assetPath + "white_queen.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	if (!gWhiteRook.loadFromFile(assetPath + "white_rook.png", gRenderer))
	{
		printf("Failed to load texture!\n");
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont((char*)(assetPath + "SlimJoe.ttf").c_str(), 18);
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
		case SDLK_q:
			retreiveMail();
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
	k.w = CHESS_SQUARE_WIDTH;
	k.h = CHESS_SQUARE_WIDTH;
	k.y = yPos;
	for (int i = 0; i < 8; i++)
	{
		k.x = i * CHESS_SQUARE_WIDTH;

		bSquares.push_back(k);
	}
}

void PrisonChess::renderChessBoard()
{

	for (int j = 0; j < 8; j++)
	{
		setUpChessBoard(j * CHESS_SQUARE_WIDTH);

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

void PrisonChess::getStringChoice(std::string str, int &currentX, int &currentY, int& moveX, int &moveY)
{
	char test;
	
	test = str.at(0);
	switch (test)
	{
	case 'A':
		currentX = A;
		break;

	case 'B':
		currentX = B;
		break;

	case 'C':
		currentX = C;
		break;

	case 'D':
		currentX = D;
		break;

	case 'E':
		currentX = E;
		break;

	case 'F':
		currentX = F;
		break;

	case 'G':
		currentX = G;
		break;

	case 'H':
		currentX = H;
		break;

	default:
		printf("\ninvalid input, try again\n");
		parseInput();
		break;
	}

	test = str.at(1);
	switch (test)
	{
	case '1':
		currentY = A;
		break;

	case '2':
		currentY = B;
		break;

	case '3':
		currentY = C;
		break;

	case '4':
		currentY = D;
		break;

	case '5':
		currentY = E;
		break;

	case '6':
		currentY = F;
		break;

	case '7':
		currentY = G;
		break;

	case '8':
		currentY = H;
		break;

	default:
		printf("\ninvalid input, try again\n");
		parseInput();
		break;
	}

	test = str.at(str.length()-2);
	switch (test)
	{
	case 'A':
		moveX = A;
		break;

	case 'B':
		moveX = B;
		break;

	case 'C':
		moveX = C;
		break;

	case 'D':
		moveX = D;
		break;

	case 'E':
		moveX = E;
		break;

	case 'F':
		moveX = F;
		break;

	case 'G':
		moveX = G;
		break;

	case 'H':
		moveX = H;
		break;

	default:
		printf("\ninvalid input, try again\n");
		parseInput();
		break;
	}

	test = str.at(str.length()-1);
	switch (test)
	{
	case '1':
		moveY = A;
		break;

	case '2':
		moveY = B;
		break;

	case '3':
		moveY = C;
		break;

	case '4':
		moveY = D;
		break;

	case '5':
		moveY = E;
		break;

	case '6':
		moveY = F;
		break;

	case '7':
		moveY = G;
		break;

	case '8':
		moveY = H;
		break;

	default:
		printf("\ninvalid input, try again\n");
		parseInput();
		break;
	}
	


	
}

int PrisonChess::findWhitePieceAtPosition(int xPos, int yPos)
{
	


	return -1;
}

int PrisonChess::findBlackPieceAtPostion(int xPos, int yPos)
{
	for (int i = 0; i < bPieces.size(); i++)
	{
		if ((bPieces[i].xPos == xPos) && (bPieces[i].yPos == yPos))
		{
			return i;
		}
	}


	return -1;
}

std::string PrisonChess::getUserInput()
{
	std::string moveStr;

	std::getline(std::cin, moveStr);

	return moveStr;
	
}

bool PrisonChess::checkMoveLogic(int piece, int newXPos, int newYPos, bool colored)
{
	printf("\n\n%i", piece);

	if (colored)
	{
		//PAWN LOGIC
		if (piece >= 8)
		{
			// Deltas
			int dx = abs(newXPos - bPieces[piece].xPos);
			int dy = abs(newYPos - bPieces[piece].yPos);

			// If move request delta-y is 2
			if ((dy == 200) && (dx == 0)) {
				// Return if pawn is on initial space
				
				return (bPieces[piece].yPos == 120);
			}
			// If move request delta-y is 1 and delta-x is 0 or 1
			return (dy == 100 && dx < 200);
		}

		if (piece == ROOK_1 || piece == ROOK_2)
		{
			// If rook is moving in only one axis
			return (!((newXPos - bPieces[piece].xPos) == 0) != !((newYPos - bPieces[piece].yPos) == 0));
		}
		if (piece == KNIGHT_1 || piece == KNIGHT_2)
		{
			int dx = abs(newXPos - bPieces[piece].xPos);
			int dy = abs(newYPos - bPieces[piece].yPos);
			return ((dx == 200 && dy == 100) || (dx == 100 && dy == 200));
		}

		if (piece == BISHOP_1 || piece == BISHOP_2)
		{
			return ((newXPos - bPieces[piece].xPos) == (newYPos - bPieces[piece].yPos));
		}

		if (piece == QUEEN)
		{
			return (
				!((newXPos - bPieces[piece].xPos) == 0) != !((newYPos - bPieces[piece].yPos) == 0) ||
				(newXPos - bPieces[piece].xPos) == (newYPos - bPieces[piece].yPos));
		}

		if (piece == KING)
		{
			int dx = abs(newXPos - bPieces[piece].xPos);
			int dy = abs(newYPos - bPieces[piece].yPos);

			return ((dx < 200) && (dy < 200));
		}

	}
	else
	{
		//PAWN LOGIC
		if (piece >= 8)
		{
			// Deltas
			int dx = abs(newXPos - wPieces[piece].xPos);
			int dy = abs(newYPos - wPieces[piece].yPos);

			// If move request delta-y is 2
			if ((dy == 200) && (dx == 0)) {
				 //Return if pawn is on initial space
				return (wPieces[piece].yPos == 120);
			}
			// If move request delta-y is 1 and delta-x is 0 or 1
			return (dy == 100 && dx < 200);
		}

		if (piece == ROOK_1 || piece == ROOK_2)
		{
			// If rook is moving in only one axis
			return (!((newXPos - wPieces[piece].xPos) == 0) != !((newYPos - wPieces[piece].yPos) == 0));
		}
		if (piece == KNIGHT_1 || piece == KNIGHT_2)
		{
			int dx = abs(newXPos - wPieces[piece].xPos);
			int dy = abs(newYPos - wPieces[piece].yPos);
			return ((dx == 200 && dy == 100) || (dx == 100 && dy == 200));
		}

		if (piece == BISHOP_1 || piece == BISHOP_2)
		{
			return ((newXPos - wPieces[piece].xPos) == (newYPos - wPieces[piece].yPos));
		}

		if (piece == QUEEN)
		{
			return (
				!((newXPos - wPieces[piece].xPos) == 0) != !((newYPos - wPieces[piece].yPos) == 0) ||
				(newXPos - wPieces[piece].xPos) == (newYPos - wPieces[piece].yPos));
		}

		if (piece == KING)
		{
			int dx = abs(newXPos - wPieces[piece].xPos);
			int dy = abs(newYPos - wPieces[piece].yPos);

			return ((dx < 200) && (dy < 200));
		}
	}
}

void PrisonChess::parseInput()
{
	std::string moveStr;
	int piece = -1;
	int pieceX = 0;
	int pieceY = 0;


	int lookX = 0;
	int lookY = 0;
	char test = ' ';



	if (whiteTurn == true)
	{
		printf("\n WHITE, enter coordinate of piece you would like to move like 'B1 to B3': \n");
		
	}
	else
	{
		printf("\n BLACK, enter coordinate of piece you would like to move like 'B1 to B3':: \n");
	}

	moveStr = getUserInput();

	getStringChoice(moveStr, pieceX, pieceY, lookX, lookY);

	printf("\n\n %i PPPPP  %i  ", pieceX, pieceY);
	printf("\n\n %i PAWN1 %i ", wPieces[8].xPos, wPieces[8].yPos);

	printf("\n\n %c   %c  ", moveStr.at(1), moveStr.at(1));



	if (whiteTurn)
	{
		//find piece in user specified place to look


		for (int i = 0; i < wPieces.size(); i++)
		{
			if ((wPieces[i].xPos == pieceX) && (wPieces[i].yPos == pieceY))
			{
				piece = i;
			}
		}
		if (piece == -1)
		{
			printf("\n NO COORDINATE FOUND AT POSITION");
			parseInput();
		}
		else
		{
			if (checkMoveLogic(piece, lookX, lookY, false))
			{
				wPieces[piece].xPos = lookX;
				wPieces[piece].yPos = lookY;
				saveScreenshotBMP("test.png", gWindow, gRenderer);
			}
			else
			{
				printf("\n YOU CANT MOVE LIKE THAT");
				parseInput();

			}
		}

	

	}
	else
	{
		for (int i = 0; i < bPieces.size(); i++)
		{
			if ((bPieces[i].xPos == pieceX) && (bPieces[i].yPos == pieceY))
			{
				piece = i;
			}

		}
		if (piece == -1)
		{
			printf("\n NO PIECE FOUND AT COORDINATE");
			parseInput();
		}
		else
		{
			if (checkMoveLogic(piece, lookX, lookY, true))
			{
				bPieces[piece].xPos = lookX;
				bPieces[piece].yPos = lookY;
				saveScreenshotBMP("test.png", gWindow, gRenderer);
			}
			else
			{
				printf("\n YOU CANT MOVE THERE!");
				parseInput();
			}

		}


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
	gBlackRook.render(gRenderer,    bPieces[ROOK_1].xPos,    bPieces[ROOK_1].yPos);
	gBlackKnight.render(gRenderer,  bPieces[KNIGHT_1].xPos,  bPieces[KNIGHT_1].yPos);
	gBlackBishop.render(gRenderer,  bPieces[BISHOP_1].xPos,  bPieces[BISHOP_1].yPos);
	gBlackQueen.render(gRenderer,   bPieces[QUEEN].xPos,     bPieces[QUEEN].yPos);

	gBlackKing.render(gRenderer,	bPieces[KING].xPos,      bPieces[KING].yPos);
	gBlackBishop.render(gRenderer,  bPieces[BISHOP_2].xPos,  bPieces[BISHOP_2].yPos);
	gBlackKnight.render(gRenderer,  bPieces[KNIGHT_2].xPos,  bPieces[KNIGHT_2].yPos);
	gBlackRook.render(gRenderer,    bPieces[ROOK_2].xPos,    bPieces[ROOK_2].yPos);

	gWhiteRook.render(gRenderer,    wPieces[ROOK_1].xPos,    wPieces[ROOK_1].yPos);
	gWhiteKnight.render(gRenderer,  wPieces[KNIGHT_1].xPos,  wPieces[KNIGHT_1].yPos);
	gWhiteBishop.render(gRenderer,  wPieces[BISHOP_1].xPos,  wPieces[BISHOP_1].yPos);
	gWhiteQueen.render(gRenderer,   wPieces[QUEEN].xPos,     wPieces[QUEEN].yPos);

	gWhiteKing.render(gRenderer,    wPieces[KING].xPos,      wPieces[KING].yPos);
	gWhiteBishop.render(gRenderer,  wPieces[BISHOP_2].xPos,  wPieces[BISHOP_2].yPos);
	gWhiteKnight.render(gRenderer,  wPieces[KNIGHT_2].xPos,  wPieces[KNIGHT_2].yPos);
	gWhiteRook.render(gRenderer,    wPieces[ROOK_2].xPos,    wPieces[ROOK_2].yPos);


	//pawns
	gWhitePawn.render(gRenderer, wPieces[PAWN_1].xPos, wPieces[PAWN_1].yPos);
	gWhitePawn.render(gRenderer, wPieces[PAWN_2].xPos, wPieces[PAWN_2].yPos);
	gWhitePawn.render(gRenderer, wPieces[PAWN_3].xPos, wPieces[PAWN_3].yPos);
	gWhitePawn.render(gRenderer, wPieces[PAWN_4].xPos, wPieces[PAWN_4].yPos);
	gWhitePawn.render(gRenderer, wPieces[PAWN_5].xPos, wPieces[PAWN_5].yPos);
	gWhitePawn.render(gRenderer, wPieces[PAWN_6].xPos, wPieces[PAWN_6].yPos);
	gWhitePawn.render(gRenderer, wPieces[PAWN_7].xPos, wPieces[PAWN_7].yPos);
	gWhitePawn.render(gRenderer, wPieces[PAWN_8].xPos, wPieces[PAWN_8].yPos);

	gBlackPawn.render(gRenderer, bPieces[PAWN_1].xPos, bPieces[PAWN_1].yPos);
	gBlackPawn.render(gRenderer, bPieces[PAWN_2].xPos, bPieces[PAWN_2].yPos);
	gBlackPawn.render(gRenderer, bPieces[PAWN_3].xPos, bPieces[PAWN_3].yPos);
	gBlackPawn.render(gRenderer, bPieces[PAWN_4].xPos, bPieces[PAWN_4].yPos);
	gBlackPawn.render(gRenderer, bPieces[PAWN_5].xPos, bPieces[PAWN_5].yPos);
	gBlackPawn.render(gRenderer, bPieces[PAWN_6].xPos, bPieces[PAWN_6].yPos);
	gBlackPawn.render(gRenderer, bPieces[PAWN_7].xPos, bPieces[PAWN_7].yPos);
	gBlackPawn.render(gRenderer, bPieces[PAWN_8].xPos, bPieces[PAWN_8].yPos);


}

//bool PrisonChess::checkIfValidMove(ChessPiece* p, int newX, int newY)
//{
//
//
//
//
//	printf("%i\n", p->pieceType);
//	
//
//	if (p->pieceType == KNIGHT_1 | p->pieceType == KNIGHT_2)
//	{
//		if ((newX == p->xPos + CHESS_SQUARE_HEIGHT))
//		{
//			if (newY == p->yPos - (CHESS_SQUARE_HEIGHT * 2))
//			{
//				return true;
//			}
//			if (newX == (p->xPos + CHESS_SQUARE_HEIGHT * 2) && (newY == (p->yPos + CHESS_SQUARE_HEIGHT * 1)))
//			{
//				return true;
//			}
//			if (newX == (p->xPos + CHESS_SQUARE_HEIGHT * 2) && (newY == (p->yPos - CHESS_SQUARE_HEIGHT * 1)))
//			{
//				return true;turn
//			}
//			if (newX == (p->xPos + CHESS_SQUARE_HEIGHT * 1) && (newY == (p->yPos + CHESS_SQUARE_HEIGHT * 2)))
//			{
//				return true;
//			}
//
//			//p->xPos+CHESS_SQUARE_HEIGHT
//			//p->yPos - (CHESS_SQUARE_HEIGHT * 2));
//			if (newX == p->xPos + CHESS_SQUARE_HEIGHT)
//			{
//				if (newY == p->yPos - (CHESS_SQUARE_HEIGHT * 2))
//				{
//					exit(1);
//					return true;
//				}
//			}
//
//			if (newX == p->xPos - CHESS_SQUARE_HEIGHT * 2)
//			{
//				if (newY == p->yPos + CHESS_SQUARE_HEIGHT * 1)
//				{
//					return true;
//				}
//			}
//
//			if (newX == (p->xPos - CHESS_SQUARE_HEIGHT * 1) && (newY == (p->yPos + CHESS_SQUARE_HEIGHT * 2)))
//			{
//				return true;
//			}
//			if (newX == (p->xPos - CHESS_SQUARE_HEIGHT * 2) && (newY == (p->yPos - CHESS_SQUARE_HEIGHT * 1)))
//			{
//				return true;
//			}
//
//			//this one
//			if (newX == (p->xPos - CHESS_SQUARE_HEIGHT * 1) && (newY == (p->yPos - CHESS_SQUARE_HEIGHT * 2)))
//			{
//				return true;
//			}
//
//		}
//
//		return false;
//	}
//}

void PrisonChess::mainLoop()
{
	retreiveMail();

	int p = 0;

	for (int i = 0; i < 16; i++)
	{
		if (i < 8)
		{

			ChessPiece k;
			bPieces.push_back(k);
		
			bPieces[i].xPos = CHESS_SQUARE_WIDTH/5 + (i*CHESS_SQUARE_WIDTH);
			bPieces[i].yPos = A;

			ChessPiece j;
			wPieces.push_back(j);
			wPieces[i].xPos = CHESS_SQUARE_WIDTH/5 + (i * CHESS_SQUARE_WIDTH);
			wPieces[i].yPos = H;

		}

		else if (i >= 8)
		{
			ChessPiece j;
			wPieces.push_back(j);
			wPieces[i].xPos = CHESS_SQUARE_WIDTH / 5 + (p*CHESS_SQUARE_WIDTH);
			wPieces[i].yPos = G;

			ChessPiece k;
			bPieces.push_back(k);
			bPieces[i].xPos = CHESS_SQUARE_WIDTH / 5 + (p*CHESS_SQUARE_WIDTH);
			bPieces[i].yPos = B;

			p++;
		}
		
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

		grid1Text.render(gRenderer, 5, A+CHESS_SQUARE_WIDTH/2);
		grid2Text.render(gRenderer, 5, B + CHESS_SQUARE_WIDTH / 2);
		grid3Text.render(gRenderer, 5, C + CHESS_SQUARE_WIDTH / 2);
		grid4Text.render(gRenderer, 5, D + CHESS_SQUARE_WIDTH / 2);
		grid5Text.render(gRenderer, 5, E + CHESS_SQUARE_WIDTH / 2);
		grid6Text.render(gRenderer, 5, F + CHESS_SQUARE_WIDTH / 2);
		grid7Text.render(gRenderer, 5, G + CHESS_SQUARE_WIDTH / 2);
		grid8Text.render(gRenderer, 5, H + CHESS_SQUARE_WIDTH / 2);

		//Update screen
		SDL_RenderPresent(gRenderer);

		if (playGame)
		{
			if (whiteTurn)
			{
				
				parseInput();
				sendMail("\n Your opponent just made a move!");
				whiteTurn = false;
				
				
			}
			else
			{

				parseInput();
				sendMail("\n Your opponent just made a move!");
				whiteTurn = true;
				
			}
			
		}
	
	}




	//SDL_WaitThread(threadID, NULL);

	//Free resources and close SDL
	close();

	getchar();
}
