#pragma once
#include <SDL.h>
#include <stdio.h>
#include "Game.h"

int main(int argc, char* args[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(802646);
	Game game = Game();
	game.Init("Gun vs Zombies", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800);

	while (game.IsRunning()) {
		game.Input();
		game.Update();
		game.Render();
	}

	return 0;
}