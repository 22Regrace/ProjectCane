#include "Enemy.h"

BasicEnemy::BasicEnemy(int health) : mEnemyHealth(health), mEnemyMoveCooldown(0), mEnemyAttackCooldown(0), mHasReachedPlayer(false), mIsEnemyAlive(true), mIsEnemyAttacking(false)
{

	mEnemyLocationSpriteSheet = { 425, 0, 35, 44 };
	mEnemyXLoc = rand() % 800;
	mEnemyYLoc = rand() % 800;
	mEnemyLocationScreen = { static_cast<int>(mEnemyXLoc), static_cast<int>(mEnemyYLoc), BASIC_ENEMY_WIDTH, BASIC_ENEMY_HEIGHT };
	mEnemyAngle = (atan2(static_cast<double> (CENTER_SCREEN_LOC - mEnemyYLoc), static_cast<double> (CENTER_SCREEN_LOC - mEnemyXLoc)) * DEGREES_TO_RADIANS);
}

void BasicEnemy::RandomizeLocation() {
	for (int i = 0; i <= SPAWNING_ATTEMPTS; i++) {
		mEnemyXLoc = (rand() % SPAWNING_RANGE) + SPAWNING_OFFSET;
		mEnemyYLoc = (rand() % SPAWNING_RANGE) + SPAWNING_OFFSET;
		int distanceFromCenter = sqrt(pow(abs(CENTER_SCREEN_LOC - mEnemyXLoc), 2) + pow(abs(CENTER_SCREEN_LOC - mEnemyYLoc), 2));
		if (distanceFromCenter >= 350 && distanceFromCenter <= 550) {
			//bounds are good
			break;
		}
	}

	mEnemyLocationScreen = { static_cast<int>(mEnemyXLoc), static_cast<int>(mEnemyYLoc), BASIC_ENEMY_WIDTH, BASIC_ENEMY_HEIGHT };
	mEnemyAngle = (atan2(static_cast<double> (CENTER_SCREEN_LOC - mEnemyYLoc), static_cast<double> (CENTER_SCREEN_LOC - mEnemyXLoc)) * DEGREES_TO_RADIANS);
};

void BasicEnemy::UpdateEnemy(const Uint32 gameClock) {
	if (!mHasReachedPlayer) {
		if (CheckEnemyMoveCooldown(gameClock)) {
			SetEnemyMoveCooldown(gameClock);
			mEnemyXLoc += NORMAL_ENEMY_SPEED * (cos(mEnemyAngle / DEGREES_TO_RADIANS));
			mEnemyYLoc += NORMAL_ENEMY_SPEED * (sin(mEnemyAngle / DEGREES_TO_RADIANS));

			mEnemyLocationScreen.x = static_cast<int>(mEnemyXLoc);
			mEnemyLocationScreen.y = static_cast<int>(mEnemyYLoc);

			if ((abs(mEnemyXLoc - CENTER_SCREEN_LOC) <= 20) && (abs(mEnemyYLoc - CENTER_SCREEN_LOC) <= 15)) {
				mHasReachedPlayer = true;
				mIsEnemyAttacking = true;
				SetEnemyAttackCooldown(gameClock);
			}

			//Simple bounds check
			if (mEnemyXLoc <= 5 || mEnemyYLoc <= 5 || mEnemyXLoc >= 795 || mEnemyYLoc >= 795) {
				mIsEnemyAlive = false;
			}
		}
	}
	else {
		mIsEnemyAttacking = CheckEnemyAttackCooldown(gameClock);
		if (mIsEnemyAttacking) {
			SetEnemyAttackCooldown(gameClock);
		}
	}
};

void BasicEnemy::SetEnemyMoveCooldown(const Uint32 gameClock) {
	mEnemyMoveCooldown = gameClock + ENEMY_MOVE_COOLDOWN;
};

bool BasicEnemy::CheckEnemyMoveCooldown(const Uint32 gameClock) const {
	return mEnemyMoveCooldown <= gameClock;
};

void BasicEnemy::SetEnemyAttackCooldown(const Uint32 gameClock) {
	mEnemyAttackCooldown = gameClock + ENEMY_ATTACK_COOLDOWN;
};

bool BasicEnemy::CheckEnemyAttackCooldown(const Uint32 gameClock) const {
	return mEnemyAttackCooldown <= gameClock;
};


void BasicEnemy::RenderEnemy(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) const {
	SDL_RenderCopyEx(gameRenderer, spriteSheet, &mEnemyLocationSpriteSheet, &mEnemyLocationScreen, mEnemyAngle, NULL, SDL_FLIP_NONE);
#ifdef _debug
	SDL_SetRenderDrawColor(gameRenderer, 255, 0, 255, 255);
	SDL_RenderDrawPoint(gameRenderer, mEnemyXLoc + HITBOX_X_OFFSET, mEnemyYLoc + HITBOX_Y_OFFSET);
#endif
}


FastEnemy::FastEnemy(int health) : mEnemyHealth(health), mEnemyMoveCooldown(0), mEnemyAttackCooldown(0), mHasReachedPlayer(false), mIsEnemyAlive(true), mIsEnemyAttacking(false)
{

	mEnemyLocationSpriteSheet = { 460, 0, 35, 44 };
	mEnemyXLoc = rand() % 800;
	mEnemyYLoc = rand() % 800;
	mEnemyLocationScreen = { static_cast<int>(mEnemyXLoc), static_cast<int>(mEnemyYLoc), BASIC_ENEMY_WIDTH, BASIC_ENEMY_HEIGHT };
	mEnemyAngle = (atan2(static_cast<double> (CENTER_SCREEN_LOC - mEnemyYLoc), static_cast<double> (CENTER_SCREEN_LOC - mEnemyXLoc)) * DEGREES_TO_RADIANS);
}

void FastEnemy::RandomizeLocation() {
	for (int i = 0; i <= SPAWNING_ATTEMPTS; i++) {
		mEnemyXLoc = (rand() % SPAWNING_RANGE) + SPAWNING_OFFSET;
		mEnemyYLoc = (rand() % SPAWNING_RANGE) + SPAWNING_OFFSET;
		int distanceFromCenter = sqrt(pow(abs(CENTER_SCREEN_LOC - mEnemyXLoc), 2) + pow(abs(CENTER_SCREEN_LOC - mEnemyYLoc), 2));
		if (distanceFromCenter >= 350 && distanceFromCenter <= 550) {
			//bounds are good
			break;
		}
	}
	mEnemyLocationScreen = { static_cast<int>(mEnemyXLoc), static_cast<int>(mEnemyYLoc), BASIC_ENEMY_WIDTH, BASIC_ENEMY_HEIGHT };
	mEnemyAngle = (atan2(static_cast<double> (CENTER_SCREEN_LOC - mEnemyYLoc), static_cast<double> (CENTER_SCREEN_LOC - mEnemyXLoc)) * DEGREES_TO_RADIANS);
};

void FastEnemy::UpdateEnemy(const Uint32 gameClock) {
	if (!mHasReachedPlayer) {
		if (CheckEnemyMoveCooldown(gameClock)) {
			SetEnemyMoveCooldown(gameClock);
			mEnemyXLoc += FAST_ENEMY_SPEED * (cos(mEnemyAngle / DEGREES_TO_RADIANS));
			mEnemyYLoc += FAST_ENEMY_SPEED * (sin(mEnemyAngle / DEGREES_TO_RADIANS));

			mEnemyLocationScreen.x = static_cast<int>(mEnemyXLoc);
			mEnemyLocationScreen.y = static_cast<int>(mEnemyYLoc);

			if ((abs(mEnemyXLoc - CENTER_SCREEN_LOC) <= 20) && (abs(mEnemyYLoc - CENTER_SCREEN_LOC) <= 15)) {
				mHasReachedPlayer = true;
				mIsEnemyAttacking = true;
				SetEnemyAttackCooldown(gameClock);
			}

			//Simple bounds check
			if (mEnemyXLoc <= 5 || mEnemyYLoc <= 5 || mEnemyXLoc >= 795 || mEnemyYLoc >= 795) {
				mIsEnemyAlive = false;
			}
		}
	}
	else {
		mIsEnemyAttacking = CheckEnemyAttackCooldown(gameClock);
		if (mIsEnemyAttacking) {
			SetEnemyAttackCooldown(gameClock);
		}
	}
};

void FastEnemy::SetEnemyMoveCooldown(const Uint32 gameClock) {
	mEnemyMoveCooldown = gameClock + ENEMY_MOVE_COOLDOWN;
};

bool FastEnemy::CheckEnemyMoveCooldown(const Uint32 gameClock) const {
	return mEnemyMoveCooldown <= gameClock;
};

void FastEnemy::SetEnemyAttackCooldown(const Uint32 gameClock) {
	mEnemyAttackCooldown = gameClock + ENEMY_ATTACK_COOLDOWN;
};

bool FastEnemy::CheckEnemyAttackCooldown(const Uint32 gameClock) const {
	return mEnemyAttackCooldown <= gameClock;
};

void FastEnemy::RenderEnemy(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) const {
	SDL_RenderCopyEx(gameRenderer, spriteSheet, &mEnemyLocationSpriteSheet, &mEnemyLocationScreen, mEnemyAngle, NULL, SDL_FLIP_NONE);
#ifdef _debug
	SDL_SetRenderDrawColor(gameRenderer, 255, 0, 255, 255);
	SDL_RenderDrawPoint(gameRenderer, mEnemyXLoc + HITBOX_X_OFFSET, mEnemyYLoc + HITBOX_Y_OFFSET);
#endif
}

