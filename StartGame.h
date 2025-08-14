#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "GameState.h"
#include "Observer.h"
#include "Command.h"
#include "UI.h"

extern class StartStateObserver;

class StartGameState : public State {
public:
	StartGameState() : mIsGameStateActive(true) {};
	~StartGameState() override {};

	void Handle(GameState* gameState) override;

	void init() override;

	void input() override;

	void update() override;

	void checkState(GameState* gameState) override;

	void render(SDL_Renderer* mRenderer, SDL_Texture* mBackgroundTexture, SDL_Texture* mSpriteSheetTexture) override;

	bool IsGameStateActive() override {
		return mIsGameStateActive;
	}

private:
	bool mIsGameStateActive;
	UI* mUI;
	Menu* mStartMenu;
	Controller* mStartMenuController;
	GoDownCommand* mGoDownCommand;
	GoUpCommand* mGoUpCommand;
	Enter* mEnterCommand;
	StartStateObserver* mObserver;
	Uint32 mGameCLock = 0;
	SDL_Rect mBackgroundLocationSheet{ 0, 670, 800, 800 };
	SDL_Rect mBackgroundLocationScreen{ 0, 0, 800, 800 };

};