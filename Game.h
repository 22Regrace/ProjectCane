#pragma once
#include <stdio.h>
#include <iostream>
#include <unordered_map> 
#include "SDL.h"
#include "SDL_image.h"
#include "GameState.h"

#define BACKGROUND_FILE_PATH "SpriteSheet/spritesheet_tiles.png"
#define SPRITE_SHEET_FILE_PATH "SpriteSheet/spritesheet_characters.png"

extern class StartGameState;

class Game {
public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height);
	void Input();
	void Update();
	void Render();
	bool IsRunning();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Texture* mBackgroundTexture;
	SDL_Texture* mSpriteSheetTexture;
	GameState *mGameState;
	State *mState;
	bool mIsGameRunning;
};
