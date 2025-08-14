#include "Command.h"

void Menu::GoingDown() {
	std::cout << " is going down \n";
	//Down will always bring you to exit option
	mUI->SetMenuSelection(Exit);
}
void Menu::GoingUp() {
	std::cout << " is going up \n";
	//Up will always bring you to startgame option
	mUI->SetMenuSelection(StartGame);
}
void Menu::Enter() {
	std::cout << " is clicking enter \n";
	//This is what the gamestate checks to see if the option the cursor is over has been selected
	mUI->SetSelectedOption();
}

void Controller::addCommand(Command* command) {
	//Pushes the most recent command onto the command vector
	mCommands.push_back(command);
}

void Controller::runCommand() {
	if (mCommands.size() != 0) {
		//Executes then erases that command from the vector
		mCommands.front()->Execute();
		mCommands.erase(mCommands.begin());
	}
}