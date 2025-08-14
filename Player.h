#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "UI.h"

#define DEGREES_TO_RADIANS 57.2957795


class Player {
public:
	Player();
	~Player();

	void RenderPlayer(SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet, SDL_Texture* backgroundSpriteSheet) const;
	void UpdatePlayer(int mCursorLocX, int mCursorLocY);
	void SetPlayerHealth(HealthBarStatus playerHealth);
	HealthBarStatus GetPlayerHealth();
	double getPlayerAngle();
	void UpdateEnemyDeathCounter() {
		mUI->UpdateEnemyDeathCounter();
	}

private:
	SDL_Rect mPlayerLocationSpriteSheet;
	SDL_Rect mPlayerLocationScreen;
	UI* mUI;
	enum HealthBarStatus mPlayerHealth;
	double mPlayerAngle;
};