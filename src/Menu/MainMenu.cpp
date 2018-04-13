#include "MainMenu.h"
#include "../States/StateManager.h"
#include "../States/Gamestate.h"
#include "../States/OptionMenuState.h"

MainMenu::MainMenu(){

	addItem(
		MenuItem("Play",
			[&]() {
		StateManager::getInstance().switchToState(new GameState(StateManager::getInstance().getWindow()));
	}));
	addItem(
		MenuItem("Options",
			[&]() {
		StateManager::getInstance().switchToState(new OptionMenuState(StateManager::getInstance().getWindow()));
	}));

	addItem(
		MenuItem("Quit",
			[&]() {
		StateManager::getInstance().quit();
	}));

}

MainMenu::~MainMenu() {
}
