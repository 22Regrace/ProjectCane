#include "Bullet.h"

BulletType::BulletType(int intrinsicState, SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) :
	mBulletID(intrinsicState), mRenderer(gameRenderer), mSpriteSheetTexture(spriteSheet),
	mBulletLocationSpriteSheet{ 468, 183, 15, 5 }
{}

BulletType::~BulletType() {}

void BulletType::renderBullet(SDL_Rect bulletLocationScreen, double bulletAngle) const {
	SDL_RenderCopyEx(mRenderer, mSpriteSheetTexture, &mBulletLocationSpriteSheet, &bulletLocationScreen, bulletAngle, NULL, SDL_FLIP_NONE);
}

Bullet::Bullet(BulletType* bulletType, BulletLoc bulletLoc, double bulletAngle, Uint32 bulletMoveCooldown, Uint32 bulletLifeCooldown, bool isBulletActive) :
	mBulletType(bulletType),mBulletLoc(bulletLoc),mBulletAngle(bulletAngle),mBulletMoveCooldown(bulletMoveCooldown),
	mBulletLifeCooldown(bulletLifeCooldown),mIsBulletActive(isBulletActive)
{}

Bullet::~Bullet() {}

void Bullet::updateBullet(const Uint32 gameClock) {
	if (CheckBulletMoveCooldown(gameClock)) {
		SetBulletMoveCooldown(gameClock);
		mBulletLoc.bulletXLoc += (2 * cos(mBulletAngle / DEGREES_TO_RADIANS));
		mBulletLoc.bulletYLoc += (2 * sin(mBulletAngle / DEGREES_TO_RADIANS));

		mBulletLoc.bulletLocationScreen.x = static_cast<int>(mBulletLoc.bulletXLoc);
		mBulletLoc.bulletLocationScreen.y = static_cast<int>(mBulletLoc.bulletYLoc);
		SetBulletLifeCooldown(gameClock);
	}
}

void Bullet::renderBullet() {
	mBulletType->renderBullet(mBulletLoc.bulletLocationScreen, mBulletAngle);
}

void Bullet::SetBulletMoveCooldown(const Uint32 gameClock) {
	mBulletMoveCooldown = gameClock + BULLET_MOVE_COOLDOWN;
};

bool Bullet::CheckBulletMoveCooldown(const Uint32 gameClock) {
	return mBulletMoveCooldown <= gameClock;
};

void Bullet::SetBulletLifeCooldown(const Uint32 gameClock) {
	if (mBulletLifeCooldown == 0) {
		mBulletLifeCooldown = gameClock + BULLET_LIFE_COOLDOWN;
	}
	else if (!CheckBulletLifeCooldown(gameClock)) {
		//Sets the bullet inactive for it to be deleted from the vector
		mIsBulletActive = false;
	}
}

bool Bullet::CheckBulletLifeCooldown(const Uint32 gameClock) {
	return mBulletLifeCooldown >= gameClock;
};

bool Bullet::getBulletState() {
	return mIsBulletActive;
}

void Bullet::SetBulletState(bool isBulletActive) {
	mIsBulletActive = isBulletActive;
}

BulletCenterLoc Bullet::GetBulletCenterLoc() {
	//TASK - if time allows it would also be ideal to improve hitbox on this, however this is a small object so less of a priority
	return { mBulletLoc.bulletXLoc, mBulletLoc.bulletYLoc };
}