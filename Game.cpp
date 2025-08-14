#include "Game.h"

Game::Game() :
	mIsGameRunning(true),
	mWindow(nullptr),
	mRenderer(nullptr),
	mBackgroundTexture(nullptr),
	mSpriteSheetTexture(nullptr)
{}

Game::~Game()
{
	delete mGameState, mState;
	SDL_DestroyTexture(mSpriteSheetTexture);
	SDL_DestroyTexture(mBackgroundTexture);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

bool Game::IsRunning() {
	return mIsGameRunning;
}

void Game::Init(const char* title, int xPos, int yPos, int width, int height) {
	//Initialize the SDL functions
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Initialization successful!" << std::endl;

		//Create the game's window and exit if that fails
		mWindow = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_SHOWN);
		if (!mWindow) {
			std::cout << "Window creation failed." << std::endl;
			exit(1);
		}

		//Create that window's renderer and exit if that fails
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
		if (!mRenderer) {
			std::cout << "Renderer creation failed." << std::endl;
			exit(1);
		}

		//Makes background surface
		SDL_Surface* temporarySurface = IMG_Load(BACKGROUND_FILE_PATH);
		if (!temporarySurface) {
			std::cout << "Texture creation failed. Could Not Find Background Texture." << std::endl;
			exit(1);
		}
		mBackgroundTexture = SDL_CreateTextureFromSurface(mRenderer, temporarySurface);
		if (!mBackgroundTexture) {
			std::cout << "Texture creation failed. Could Create Texture From Surface." << std::endl;
			exit(1);
		}


		//Makes the sprite sheet
		temporarySurface = IMG_Load(SPRITE_SHEET_FILE_PATH);
		if (!temporarySurface) {
			std::cout << "Texture creation failed. Could Not Find Sprite Sheet Texture." << std::endl;
			exit(1);
		}
		mSpriteSheetTexture = SDL_CreateTextureFromSurface(mRenderer, temporarySurface);
		if (!mSpriteSheetTexture) {
			std::cout << "Texture creation failed. Could Create Texture From Surface." << std::endl;
			exit(1);
		}
	}
	mGameState = new GameState(nullptr);
	mState = mGameState->getState();
	mState->init();
}

void Game::Input() {
	mState->checkState(mGameState);
	mState = mGameState->getState();
	mState->input();
	mIsGameRunning = mState->IsGameStateActive();
}

void Game::Update() {
	mState->update();
}

void Game::Render() {
	mState->render(mRenderer, mBackgroundTexture, mSpriteSheetTexture);
	SDL_RenderPresent(mRenderer);
}