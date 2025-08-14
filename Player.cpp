#include "Player.h"

Player::Player():
	mPlayerLocationScreen{370, 375, 55, 45},
	mPlayerLocationSpriteSheet{109, 132, 55, 43}, //109 x for symmetric
	mPlayerHealth(ThreeHearts),
	mPlayerAngle(0)
{
mUI = new UI();
}
Player::~Player() {
	delete mUI;
}

void Player::UpdatePlayer(int mCursorLocX, int mCursorLocY) {
	if (mCursorLocX != mPlayerLocationScreen.x) {
		mPlayerAngle =( atan2(static_cast<double> (mCursorLocY - mPlayerLocationScreen.y), static_cast<double> (mCursorLocX - mPlayerLocationScreen.x)) * DEGREES_TO_RADIANS);
	}
}

void Player::SetPlayerHealth(HealthBarStatus playerHealth){
	mPlayerHealth = playerHealth;
}

void Player::RenderPlayer(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet, SDL_Texture* backgroundSpriteSheet) const {
	mUI->RenderHealth(mPlayerHealth, gameRenderer, spriteSheet);
	mUI->RenderScore(gameRenderer, backgroundSpriteSheet);
	SDL_RenderCopyEx(gameRenderer, spriteSheet, &mPlayerLocationSpriteSheet, &mPlayerLocationScreen, mPlayerAngle, NULL, SDL_FLIP_NONE);
}

HealthBarStatus Player::GetPlayerHealth(){
	return mPlayerHealth;
}

double Player::getPlayerAngle() {
	return mPlayerAngle;
}