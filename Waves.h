#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#define MAX_WAVE_NUMBER 10
#define MINIMUM_ENEMY_AMOUNT 1
#define COLLISION_DISTANCE 25
#define BASIC_ENEMY_HEALTH 5

class Waves {
public:
	Waves();
	~Waves();
	void SpawnWave();
	void UpdateWave(Player* player, std::vector<Bullet*> bullets, const Uint32 gameClock);
	void RenderWave(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet);
private:
	int mCurrentWaveNumber;
	std::vector<std::vector<Enemy*>> mEnemyVector;
};
