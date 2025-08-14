#include "UI.h"

UI::UI() : mHasBeenSelected(false), mNumEnemiesKilled(0), mCurrentMenuSelection(StartGame)
{
	mSkullLocSpriteSheet = { 1354, 306, 160, 130 };
	mSkullLocScreen = { 500, 20, 100, 82 };
	mNumberLocScreen = { 600, 20, NUMBER_WIDTH, NUMBER_HEIGHT };
	mHealthLocSpriteSheet = { 460, 132, 40, 44 };
	mHealthLocScreen = { 125, 20, 40, 44 };
	mMenuCursorSpriteSheet = { 1323, 593, 163, 61 };
	mMenuCursorLocation.push_back({ 75, 360, 112, 36 });
	mMenuCursorLocation.push_back({175, 570, 112, 36 });
}

UI::~UI(){}

void UI::SetMenuSelection(StartMenuOptions menuSelection)
{
	mCurrentMenuSelection = menuSelection;
}

void UI::RenderHealth(HealthBarStatus health, SDL_Renderer* gameRenderer, SDL_Texture* spriteSheet)
{
	//Sets x value back to inital position
	mHealthLocScreen.x = 125;
	for (int i = 1; i <= health; i++) {
		SDL_RenderCopy(gameRenderer, spriteSheet, &mHealthLocSpriteSheet, &mHealthLocScreen);
		mHealthLocScreen.x -= 50;
	}
}

void UI::RenderMenuCursor(SDL_Renderer* gameRenderer, SDL_Texture* backgroundSpriteSheet) {
	SDL_RenderCopy(gameRenderer, backgroundSpriteSheet, &mMenuCursorSpriteSheet, &mMenuCursorLocation[static_cast<int>(mCurrentMenuSelection)]);
}

void UI::RenderScore(SDL_Renderer* gameRenderer, SDL_Texture* backgroundSpriteSheet) {
	SDL_RenderCopy(gameRenderer, backgroundSpriteSheet, &mSkullLocSpriteSheet, &mSkullLocScreen);
	std::string tempString = std::to_string(mNumEnemiesKilled);
	for (int i = 0; i < tempString.size(); i++) {
	int targetCharacterAscii = tempString[i];
	if ((targetCharacterAscii >= 48) && (targetCharacterAscii <= 57)) {
		targetCharacterAscii = targetCharacterAscii - 48;
		SDL_Rect numLocationSpriteSheet = { mNumberSpriteSheetCoordinates[targetCharacterAscii][0],mNumberSpriteSheetCoordinates[targetCharacterAscii][1], NUMBER_WIDTH, NUMBER_HEIGHT };
		mNumberLocScreen.x = NUMBER_STARTING_X + (NUMBER_OFFSET * i);
		SDL_RenderCopy(gameRenderer, backgroundSpriteSheet, &numLocationSpriteSheet, &mNumberLocScreen);
	}
	else {
		std::cout << "The number requested to print is out of range \n";
	}
	}
}
