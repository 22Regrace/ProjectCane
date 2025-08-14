#include "EndGame.h"
#include "StartGame.h"

void EndGameState::Handle(GameState* gameState) {
	State* nextGamestate = new InGameGameState();
	changeState(nextGamestate, gameState);
	delete mObserver;
	delete mMenu, mMenuController;
	delete mGoUpCommand, mGoDownCommand, mEnterCommand;
	delete this;
	//Include reset game logic here 
	gameState->getState()->init();
}

void EndGameState::init() {
	mObserver = new EndStateObserver();
	mUI = new UI();
	mMenu = new Menu("EndScreenMenu", mUI);
	mMenuController = new Controller();
	mGoDownCommand = new GoDownCommand(*mMenu);
	mGoUpCommand = new GoUpCommand(*mMenu);
	mEnterCommand = new Enter(*mMenu);
};

void EndGameState::input() {
	SDL_Event Event;
	while (SDL_PollEvent(&Event) != 0) {
		if (Event.type == SDL_KEYDOWN) {
			if (Event.key.keysym.sym == SDLK_DOWN) {
				mMenuController->addCommand(mGoDownCommand);
			}
			else if (Event.key.keysym.sym == SDLK_UP) {
				mMenuController->addCommand(mGoUpCommand);
			}
			else if (Event.key.keysym.sym == SDLK_KP_ENTER) {
				mMenuController->addCommand(mEnterCommand);
			}
		}
	}
};

void EndGameState::update() {
	mMenuController->runCommand();
};

void EndGameState::checkState(GameState* gameState) {
	if (mUI->GetSelectedOption()) {
		if (mUI->GetMenuSelection() == StartGame) {
			mObserver->Update(this, gameState);
		}
		else {
			delete mObserver;
			delete mMenu, mMenuController;
			delete mGoUpCommand, mGoDownCommand, mEnterCommand;
			std::cout << "Ending Program \n";
			mIsGameStateActive = false;
		}
	}
};

void EndGameState::render(SDL_Renderer* mRenderer, SDL_Texture* mBackgroundTexture, SDL_Texture* mSpriteSheetTexture) {
	SDL_RenderCopy(mRenderer, mBackgroundTexture, &mBackgroundLocationSheet, &mBackgroundLocationScreen);
	mUI->RenderMenuCursor(mRenderer, mBackgroundTexture);
};