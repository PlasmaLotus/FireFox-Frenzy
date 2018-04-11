#include "PauseMenu.h"
#include "../States/StateManager.h"
#include "../States/TitleScreen.h"

PauseMenu::~PauseMenu(){
}

PauseMenu::PauseMenu(){
	addItem(
		MenuItem("Back To Game",
			[&]() {
		StateManager::getInstance().goBack();
	}));
	addItem(
		MenuItem("Quit",
			[&]() {
		StateManager::getInstance().switchToState(new TitleScreen(StateManager::getInstance().getWindow()));
	}));
}
