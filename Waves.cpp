#include "Waves.h"

Waves::Waves() : mCurrentWaveNumber(0) {
	SpawnWave();
}
Waves::~Waves() {
	for (int i = 0; i < mEnemyVector[mCurrentWaveNumber].size(); i++) {
		delete mEnemyVector[mCurrentWaveNumber][i];
	}
	mEnemyVector.clear();
}

void Waves::SpawnWave() {
	EnemyFactory EnemyFactory(5);
	Enemy* BasicEnemy = EnemyFactory.CreateEnemy(basicEnemy);
	Enemy* FastEnemy = EnemyFactory.CreateEnemy(fastEnemy);
	std::vector<Enemy*> waveEnemies;
	for (int j = (rand() % (mCurrentWaveNumber+MINIMUM_ENEMY_AMOUNT)); j >= 0 ; --j) {
		int enemyTypeGenerator = rand() % 10;
		if (enemyTypeGenerator <= 1) {
			waveEnemies.push_back(FastEnemy->Clone());
		}
		else {
			waveEnemies.push_back(BasicEnemy->Clone());
		}

	}
	mEnemyVector.push_back(waveEnemies);
}

void Waves::UpdateWave(Player* player, std::vector<Bullet*> bullets, const Uint32 gameClock) {
	for (int i = 0; i < mEnemyVector[mCurrentWaveNumber].size(); i++) {
		mEnemyVector[mCurrentWaveNumber][i]->UpdateEnemy(gameClock);
		if (!mEnemyVector[mCurrentWaveNumber][i]->GetEnemyState()) {
			//delete mEnemyVector[mCurrentWaveNumber][i];
			mEnemyVector[mCurrentWaveNumber].erase(mEnemyVector[mCurrentWaveNumber].begin() + i);
		} else if (mEnemyVector[mCurrentWaveNumber][i]->GetIsEnemyAttacking()) {
			//There has to be a better way to do this then passing the player pointer
			player->SetPlayerHealth(static_cast<HealthBarStatus>(player->GetPlayerHealth() - OneHeart));
		}
	}

	//TASK - If time provides reconfigure this simple collision system, hopefully making use of a grid so all objects wont have to check every other object
	//right now it is causing no noticable slowdowns, but could be an issue to watch for in future.
	for (int i = 0; i < bullets.size(); i++) {
		for (int j = 0; j < mEnemyVector[mCurrentWaveNumber].size(); j++) {
			//Using the distance formula to get the distance between a given enemy and the bullet
			BulletCenterLoc bulletCenterLoc = bullets[i]->GetBulletCenterLoc();
			EnemyCenterLoc enemyCenterLoc = mEnemyVector[mCurrentWaveNumber][j]->GetEnemyCenterLoc();
			//Checks collision between bullets and Enemy
			if ((sqrt(pow(abs(bulletCenterLoc.bulletCenterXLoc - enemyCenterLoc.enemyCenterXLoc), 2) + pow(abs(bulletCenterLoc.bulletCenterYLoc - enemyCenterLoc.enemyCenterYLoc), 2))) <= COLLISION_DISTANCE) {
				//Sets the enemy to not alive
				mEnemyVector[mCurrentWaveNumber][j]->SetEnemyState(false);
				//Sets the colliding bullet to inactive to be removed from the vector and deleted next update call
				bullets[i]->SetBulletState(false);
				std::cout << "Enemy Hit! Playing death animation! \n";
				player->UpdateEnemyDeathCounter();
				break;
			}
		}
	}

	if (mEnemyVector[mCurrentWaveNumber].size() == 0) {
		//Starts the next wave
		mCurrentWaveNumber++;
		SpawnWave();
	}
}

void Waves::RenderWave(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) {
	for (int i = 0; i < mEnemyVector[mCurrentWaveNumber].size(); i++) {
		mEnemyVector[mCurrentWaveNumber][i]->RenderEnemy(gameRenderer, spriteSheet);
	}
}