#pragma once
#include <iostream>
#include <unordered_map>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "math.h"

#define DEGREES_TO_RADIANS 57.2957795
#define BULLET_MOVE_COOLDOWN 7
#define BULLET_LIFE_COOLDOWN 2200

class Bullet;

/// <summary>
/// includes the information on where the bullet is located with its exact X & Y location being stored as a double, and the bullet location on screen being stored as an SDL_Rect
/// </summary>
struct BulletLoc {
	double bulletXLoc;
	double bulletYLoc;
	SDL_Rect bulletLocationScreen;
};

/// <summary>
/// Includes the location of the center of the bullet X & Y location which is used for collision detection
/// </summary>
struct BulletCenterLoc {
	double bulletCenterXLoc;
	double bulletCenterYLoc;
};

class BulletType {
public:
	BulletType(int mBulletID, SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet);
	virtual ~BulletType();

	void renderBullet(SDL_Rect bulletLocationScreen, double bulletAngle) const;

private:
	int mBulletID;
	SDL_Rect mBulletLocationSpriteSheet;
	SDL_Renderer* mRenderer;
	SDL_Texture* mSpriteSheetTexture;
};

class Bullet{
public:
	Bullet(BulletType* bulletType, BulletLoc bulletLoc, double bulletAngle, Uint32 bulletMoveCooldown, Uint32 bulletLifeCooldown, bool isBulletActive);
	virtual ~Bullet();

	void updateBullet(const Uint32 gameClock);

	void SetBulletMoveCooldown(const Uint32 gameClock);

	bool CheckBulletMoveCooldown(const Uint32 gameClock);

	void SetBulletLifeCooldown(const Uint32 gameClock);

	bool CheckBulletLifeCooldown(const Uint32 gameClock);

	void renderBullet();

	BulletCenterLoc GetBulletCenterLoc();

	void SetBulletState(bool isBulletActive);
	
	//Returns if bullet is active
	bool getBulletState();
private:
	BulletType* mBulletType;
	BulletLoc mBulletLoc;
	double mBulletAngle;
	Uint32 mBulletMoveCooldown;
	Uint32 mBulletLifeCooldown;
	bool mIsBulletActive;
};

class BulletFactory {
public:
	BulletType* getBulletType(int key, SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet) {
		if (mBullets.find(key) == mBullets.end()) {
			mBullets[key] = new BulletType(key, gameRenderer, spriteSheet);
		}
		return mBullets[key];
	}
private: 
	std::unordered_map<int, BulletType*> mBullets;
};