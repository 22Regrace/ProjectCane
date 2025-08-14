#include "Observer.h"
#include "GameState.h"

void StartStateObserver::Update(State* state, GameState* gameState) {
	state->Handle(gameState);
}

void InGameStateObserver::Update(State* state, GameState* gameState){
	state->Handle(gameState);
}

void EndStateObserver::Update(State* state, GameState* gameState){
	state->Handle(gameState);
}
