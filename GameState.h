#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"

extern class State;

class GameState {
public:
	GameState(State *state);
	virtual ~GameState();
	void setGameState(State *state);
	State* getState();

private:
	//This is used so the other changeState function (in the state class) can call this changeState which changes the state in the actual GameState framework.
	friend class State;
	void changeState(State* state);
	State* mState;
};

class State {
public:
	State() {};
	virtual ~State();

	virtual void Handle(GameState* gameState) {};
	virtual void init() {};
	virtual void input() {};
	virtual void update() {};
	virtual bool IsGameStateActive() = 0;

	//Question-> How could I better implement this. Right now I have the checkState which is just for the observer so it doesn't have to have the gamestate passed into update everytime for it to 
	//mainly go unused. I think there is a possibility I could combine Gamestate and my observers but I feel like that would be a significant rework and I am not sure if that would be worth it with time
	//thanks Utsab!
	virtual void checkState(GameState* gameState) {};
	virtual void render(SDL_Renderer* mRenderer, SDL_Texture* mBackgroundTexture, SDL_Texture* mSpriteSheetTexture) {};

protected:
	void changeState(State* state, GameState* gameState);
};
