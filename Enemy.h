#pragma once
#include <iostream>
#include <unordered_map>
#include <math.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"

#define BASIC_ENEMY_WIDTH 35
#define BASIC_ENEMY_HEIGHT 44
#define CENTER_SCREEN_LOC 390
#define ENEMY_MOVE_COOLDOWN 35
#define ENEMY_ATTACK_COOLDOWN 2000
#define DEGREES_TO_RADIANS 57.2957795
#define ENEMY_Y_HITBOX_OFFSET 5
#define FAST_ENEMY_SPEED 4.5
#define NORMAL_ENEMY_SPEED 1.6
#define HITBOX_X_OFFSET 8
#define HITBOX_Y_OFFSET 10
#define SPAWNING_RANGE 780
#define SPAWNING_OFFSET 10
#define SPAWNING_ATTEMPTS 100

extern class Enemy;
extern class BasicEnemy;
extern class FastEnemy;

/// <summary>
/// Holds the exact x and y location of the enemy used for checking collision
/// </summary>
struct EnemyCenterLoc {
	double enemyCenterXLoc;
	double enemyCenterYLoc;
};

enum EnemyType {
	basicEnemy,
	fastEnemy
};

class Enemy {
public:
	virtual Enemy* Clone() = 0;
	virtual void RenderEnemy(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) const = 0;
	virtual void UpdateEnemy(const Uint32 gameClock) = 0;
	virtual void RandomizeLocation() = 0;
	virtual EnemyCenterLoc GetEnemyCenterLoc() = 0;
	virtual void SetEnemyState(bool isEnemyAlive) = 0;
	virtual bool GetEnemyState() const = 0;
	virtual bool GetIsEnemyAttacking() = 0;	
	virtual void SetEnemyMoveCooldown(const Uint32 gameClock) = 0;
	virtual bool CheckEnemyMoveCooldown(const Uint32 gameClock) const = 0;
	virtual void SetEnemyAttackCooldown(const Uint32 gameClock) = 0;
	virtual bool CheckEnemyAttackCooldown(const Uint32 gameClock) const = 0;
	virtual ~Enemy() = default;
};

class BasicEnemy : public Enemy {
public:
	BasicEnemy(int health);

	Enemy* Clone() override {
		BasicEnemy* clonedEnemy = new BasicEnemy(5);
		clonedEnemy->RandomizeLocation();
		return clonedEnemy;
	}

	void RenderEnemy(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) const override;

	void RandomizeLocation() override;

	void UpdateEnemy(const Uint32 gameClock) override;

	void SetEnemyState(bool isEnemyAlive) override {
		mIsEnemyAlive = isEnemyAlive;
	}

	bool GetEnemyState() const override {
		return mIsEnemyAlive;
	}

	bool GetIsEnemyAttacking() override {
		return mIsEnemyAttacking;
	}

	EnemyCenterLoc GetEnemyCenterLoc() override {
		return { mEnemyXLoc + HITBOX_X_OFFSET, mEnemyYLoc + HITBOX_Y_OFFSET };
	}

	void SetEnemyMoveCooldown(const Uint32 gameClock) override;

	bool CheckEnemyMoveCooldown(const Uint32 gameClock) const override;

	void SetEnemyAttackCooldown(const Uint32 gameClock) override;

	bool CheckEnemyAttackCooldown(const Uint32 gameClock) const override;

private:
	SDL_Rect mEnemyLocationSpriteSheet;
	SDL_Rect mEnemyLocationScreen;
	Uint32 mEnemyMoveCooldown;
	Uint32 mEnemyAttackCooldown;
	double mEnemyXLoc;
	double mEnemyYLoc;
	double mEnemyAngle;
	bool mHasReachedPlayer;
	bool mIsEnemyAttacking;
	bool mIsEnemyAlive;
	int mEnemyHealth;
};


class FastEnemy : public Enemy {
public:
	FastEnemy(int health);

	Enemy* Clone() override {
		FastEnemy* clonedEnemy = new FastEnemy(5);
		clonedEnemy->RandomizeLocation();
		return clonedEnemy;
	}

	void RandomizeLocation() override;

	void UpdateEnemy(const Uint32 gameClock) override;

	void RenderEnemy(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) const override;

	void SetEnemyState(bool isEnemyAlive) override {
		mIsEnemyAlive = isEnemyAlive;
	}

	bool GetEnemyState() const override {
		return mIsEnemyAlive;
	}

	bool GetIsEnemyAttacking() override {
		return mIsEnemyAttacking;
	}

	EnemyCenterLoc GetEnemyCenterLoc() override {
		return { mEnemyXLoc + HITBOX_X_OFFSET, mEnemyYLoc + HITBOX_Y_OFFSET };
	}

	void SetEnemyMoveCooldown(const Uint32 gameClock) override;

	bool CheckEnemyMoveCooldown(const Uint32 gameClock) const override;

	void SetEnemyAttackCooldown(const Uint32 gameClock) override;

	bool CheckEnemyAttackCooldown(const Uint32 gameClock) const override;

private:
	SDL_Rect mEnemyLocationSpriteSheet;
	SDL_Rect mEnemyLocationScreen;
	Uint32 mEnemyMoveCooldown;
	Uint32 mEnemyAttackCooldown;
	double mEnemyXLoc;
	double mEnemyYLoc;
	double mEnemyAngle;
	bool mHasReachedPlayer;
	bool mIsEnemyAttacking;
	bool mIsEnemyAlive;
	int mEnemyHealth;
};

class EnemyFactory {
public:
	EnemyFactory(int health) {
		mEnemies[basicEnemy] = new BasicEnemy(health);
		mEnemies[fastEnemy] = new FastEnemy(health);
	}
	~EnemyFactory(){
		delete mEnemies[basicEnemy], mEnemies[fastEnemy];
	}

	Enemy* CreateEnemy(EnemyType enemyType) {
		if(enemyType == basicEnemy){
			return mEnemies[basicEnemy]->Clone();
		}
		else if (enemyType == fastEnemy) {
			return mEnemies[fastEnemy]->Clone();
		}
		else {
			return nullptr;
		}
	}

private:
	 Enemy* mEnemies[2];
};

