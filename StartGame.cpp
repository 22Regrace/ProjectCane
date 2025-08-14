#include "StartGame.h"
#include "InGame.h"

void StartGameState::Handle(GameState* gameState) {
	State* nextGamestate = new InGameGameState();
	changeState(nextGamestate, gameState);
	delete mObserver;
	delete mUI;
	delete mStartMenu, mStartMenuController;
	delete mGoUpCommand, mGoDownCommand, mEnterCommand;
	delete this;
	//Initalizes the next state
	gameState->getState()->init();
}

void StartGameState::init() {
	srand(time(NULL));
	mObserver = new StartStateObserver();
	mUI = new UI();
	mStartMenu = new Menu("StartMenu", mUI);
	mStartMenuController = new Controller();
	mGoDownCommand = new GoDownCommand(*mStartMenu);
	mGoUpCommand = new GoUpCommand(*mStartMenu);
	mEnterCommand = new Enter(*mStartMenu);
};

void StartGameState::input() {
	SDL_Event Event;
	while (SDL_PollEvent(&Event) != 0) {
		if (Event.type == SDL_KEYDOWN) {
			if (Event.key.keysym.sym == SDLK_DOWN) {
				mStartMenuController->addCommand(mGoDownCommand);
			} 
			else if (Event.key.keysym.sym == SDLK_UP) {
				mStartMenuController->addCommand(mGoUpCommand);
			}
			else if (Event.key.keysym.sym == SDLK_KP_ENTER) {
				mStartMenuController->addCommand(mEnterCommand);
			}
		} 
	}
};

void StartGameState::update() {
	mGameCLock = SDL_GetTicks();
	mStartMenuController->runCommand();
};

void StartGameState::checkState(GameState* gameState) {
	if (mUI->GetSelectedOption()) {
		if (mUI->GetMenuSelection() == StartGame) {
			mObserver->Update(this, gameState);
		}
		else {
			delete mObserver;
			delete mStartMenu, mStartMenuController;
			delete mGoUpCommand, mGoDownCommand, mEnterCommand;
			std::cout << "Ending Program \n";
			mIsGameStateActive = false;
		}
	}
}

void StartGameState::render(SDL_Renderer* mRenderer, SDL_Texture* mBackgroundTexture, SDL_Texture* mSpriteSheetTexture) {
	SDL_RenderCopy(mRenderer, mBackgroundTexture, &mBackgroundLocationSheet, &mBackgroundLocationScreen);
	mUI->RenderMenuCursor(mRenderer, mBackgroundTexture);
};