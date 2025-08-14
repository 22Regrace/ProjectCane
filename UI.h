#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"

#define NUMBER_WIDTH 60
#define NUMBER_HEIGHT 78
#define NUMBER_OFFSET 42
#define NUMBER_STARTING_X 600

enum HealthBarStatus{
NoHearts,
OneHeart,
TwoHearts,
ThreeHearts
};

enum StartMenuOptions {
StartGame,
Exit
};

class UI {
public:
	const int mNumberSpriteSheetCoordinates[10][2]{
		{1835, 402},
		{1560, 300},
		{1630, 300},
		{1700, 300},
		{1760, 300},
		{1830, 300},
		{1560, 402},
		{1630, 402},
		{1700, 402},
		{1765, 402},
	};

	UI();
	~UI();
	void SetMenuSelection(StartMenuOptions menuSelection);
	StartMenuOptions GetMenuSelection() {
		return mCurrentMenuSelection;
	}
	void SetSelectedOption() {
		//Current option will be the option executed
		mHasBeenSelected = true;
	}
	bool GetSelectedOption() {
		return mHasBeenSelected;
	}
	void RenderHealth(HealthBarStatus health, SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet);
	void RenderMenuCursor(SDL_Renderer* gameRenderer, SDL_Texture* backgroundSpriteSheet);
	void UpdateEnemyDeathCounter() {
		mNumEnemiesKilled++;
	}
	void RenderScore(SDL_Renderer* gameRenderer, SDL_Texture* backgroundSpriteSheet);
private:
	int mNumEnemiesKilled;
	SDL_Rect mNumberLocScreen;
	SDL_Rect mSkullLocScreen;
	SDL_Rect mSkullLocSpriteSheet;
	SDL_Rect mMenuCursorSpriteSheet;
	std::vector<SDL_Rect> mMenuCursorLocation;
	SDL_Rect mHealthLocSpriteSheet;
	SDL_Rect mHealthLocScreen;
	StartMenuOptions mCurrentMenuSelection;
	bool mHasBeenSelected;
};