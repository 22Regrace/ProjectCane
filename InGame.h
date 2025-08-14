#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_events.h"
#include "GameState.h"
#include "Player.h"
#include "Bullet.h"
#include "Waves.h"
#include "Observer.h"

#define CENTER_SCREEN_LOC 390
#define SHOOTING_COOLDOWN 800
#define BULLET_START_RECT { 400, 400, 15, 5 }

extern class InGameStateObserver;

enum {
	REGULAR_BULLET,
};

class InGameGameState : public State {
public:
	InGameGameState() : mIsGameStateActive(true), mIsShooting(false) {};
	~InGameGameState() override {};
	void Handle(GameState* gameState) override;
	void init() override;
	void input() override;
	void update() override;
	void checkState(GameState* gameState) override;
	void render(SDL_Renderer* mRenderer, SDL_Texture* mBackgroundTexture, SDL_Texture* mSpriteSheetTexture) override;
	bool IsGameStateActive() override {
		return mIsGameStateActive;
	}

	void SetShootingCooldown(Uint32 gameClock) {
		mShootingCooldown = gameClock + SHOOTING_COOLDOWN;
	};

	bool CheckShootingCooldown(Uint32 gameClock) {
		return mShootingCooldown <= gameClock;
	};



private:
	bool mIsShooting;
	bool mIsGameStateActive;
	Waves* mWaves;
	Player* mPlayer;
	InGameStateObserver *mObserver;
	BulletFactory mBulletFactory;
	Uint32 mGameCLock;
	SDL_Rect mBackgroundLocationSheet{ 296, 222, 63, 63 };
	SDL_Rect mBackgroundLocationScreen{ 0, 0, 800, 800 };
	int mCursorLocX;
	int mCursorLocY;
	std::vector<Bullet*> mBullets;
	Uint32 mShootingCooldown;
};