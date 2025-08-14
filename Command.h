#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "UI.h"

class Menu {
public:
	Menu(const std::string& name, UI* UI) : mMenuName(name), mUI(UI) {};
	void GoingDown();
	void GoingUp();
	void Enter();
private:
	std::string mMenuName;
	UI* mUI;
};

class Command {
public:
	virtual void Execute() = 0;
};

class GoDownCommand : public Command {
public: 
	GoDownCommand(Menu &menu) : mMenu(menu) {};
	void Execute() override { mMenu.GoingDown(); }
private: 
	Menu& mMenu;
};

class GoUpCommand : public Command {
public:
	GoUpCommand(Menu &menu) : mMenu(menu) {};
	void Execute() override { mMenu.GoingUp(); }
private:
	Menu& mMenu;
};

class Enter : public Command {
public:
	Enter(Menu &menu) : mMenu(menu) {};
	void Execute() override { mMenu.Enter(); }
private:
	Menu& mMenu;
};

class Controller {
public:
	Controller() { }
	~Controller() { }
	void addCommand(Command* command);
	void runCommand();
private:
	std::vector <Command*> mCommands;
};