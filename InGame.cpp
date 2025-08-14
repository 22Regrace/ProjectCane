#include "InGame.h"
#include "EndGame.h"

void InGameGameState::Handle(GameState* gameState) {
	State* nextGamestate = new EndGameState();
	changeState(nextGamestate, gameState);
	delete mPlayer;
	delete mWaves;
	delete mObserver;
	for (int i = 0; i < mBullets.size(); i++) {
		delete mBullets[i];
	}
	//Initializes the ending screen
	gameState->getState()->init();
}

void InGameGameState::init(){
	mPlayer = new Player();
	mShootingCooldown = 0;
	mWaves = new Waves();
	mObserver = new InGameStateObserver();
}

void InGameGameState::input(){
	SDL_Event Event;
	while (SDL_PollEvent(&Event) != 0) {
		if (Event.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&mCursorLocX, &mCursorLocY);
		}
		if (!mIsShooting && Event.type == SDL_MOUSEBUTTONDOWN) {
			//TASK make mIsShooting into a command structure, that way it knows how many times you clicked and can open doors for things like rounds/reloading
			mIsShooting = true;
		}
	}
}

void InGameGameState::update() {
	mGameCLock = SDL_GetTicks();
	mPlayer->UpdatePlayer(mCursorLocX, mCursorLocY);
	//Updates all active bullets
	for (int i = 0; i < mBullets.size(); i++) {
		mBullets[i]->updateBullet(mGameCLock);
		//if bullet is not active delete it from the vector
		if (!mBullets[i]->getBulletState()) {
			delete mBullets[i];
			mBullets.erase(mBullets.begin() + i);
		}
	}
	mWaves->UpdateWave(mPlayer, mBullets, mGameCLock);
}

void InGameGameState::checkState(GameState* gameState) {
	if (mPlayer->GetPlayerHealth() == 0) {
		mObserver->Update(this, gameState);
	}
};

void InGameGameState::render(SDL_Renderer* mRenderer, SDL_Texture* mBackgroundTexture, SDL_Texture* mSpriteSheetTexture) {
	SDL_RenderCopy(mRenderer, mBackgroundTexture, &mBackgroundLocationSheet, &mBackgroundLocationScreen);
	mWaves->RenderWave(mRenderer, mSpriteSheetTexture);
	for (int i = 0; i < mBullets.size(); i++) {
		mBullets[i]->renderBullet();
	}
	mPlayer->RenderPlayer(mRenderer, mSpriteSheetTexture, mBackgroundTexture);

	//Checks to see if a new bullet can be shot and shoots if so
	//Located here instead of updated because if a bullet type is not created it needs renderer and spritesheet information
	if (CheckShootingCooldown(mGameCLock) && mIsShooting == true) {
		mIsShooting = false;
		SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
		SDL_Rect tempRect = { 405, 412, 15, 5 };
		Bullet* tempBullet = new Bullet(mBulletFactory.getBulletType(REGULAR_BULLET, mRenderer, mSpriteSheetTexture), {CENTER_SCREEN_LOC, CENTER_SCREEN_LOC, tempRect},
					static_cast<double>(mPlayer->getPlayerAngle()), 0 , 0, true);
		mBullets.push_back(tempBullet);
		SetShootingCooldown(mGameCLock);
	}
}
