#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "StartGame.h"
#include "InGame.h"
#include "EndGame.h"

class Observer{
public:
	Observer() {};
	virtual ~Observer() {};
	virtual void Update(State* state, GameState* gameState) {};
};

//Not combining these observers in case I have time to go back later to put in an intro screen or put them on timers. If time allows, these will differentiate. TASK.

class StartStateObserver : public Observer{
public:
	StartStateObserver() {};
	~StartStateObserver() {};
	void Update(State* state, GameState* gameState) override;
};

class InGameStateObserver : public Observer {
public:
	InGameStateObserver() {};
	~InGameStateObserver() {};
	void Update(State* state, GameState* gameState) override;
};

class EndStateObserver : public Observer {
public:
	EndStateObserver() {};
	~EndStateObserver() {};
	void Update(State* state, GameState* gameState) override;
};