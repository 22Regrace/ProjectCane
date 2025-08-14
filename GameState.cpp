#pragma once
#include "GameState.h"
#include "StartGame.h"
#include "InGame.h"
#include "EndGame.h"

GameState::GameState(State *state) : mState(new StartGameState) {};
GameState::~GameState() {};

void GameState::setGameState(State* state) {
	if (state == nullptr) {
		mState = new StartGameState();
	}
	else {
		delete mState;
		mState = state;
	}

};

State* GameState::getState() {
	return mState;
}

void GameState::changeState(State* state) {
	mState = state;
}

State::~State() {}

void State::changeState(State* state, GameState* gameState) {
	gameState->changeState(state);
}