#include "PauseMenu.h"
#include "../States/StateManager.h"
#include "../States/TitleScreen.h"
#include "../States/GameState.h"

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


PauseMenu::PauseMenu(GameState* gs):
	gameState{ gs } {
	addItem(
		MenuItem("Back To Game",
			[&]() {
		StateManager::getInstance().goBack();
	}));

	addItem(
		MenuItem("Toggle FPS",
			[&]() {
		if (gameState != nullptr) { gameState->getRenderer()->toggleFPS(); };
	}));

	addItem(
		MenuItem("Toggle Player Positions ",
			[&]() {
		if (gameState != nullptr) { gameState->getRenderer()->togglePositions();};
	}));

	addItem(
		MenuItem("Toggle Hitboxes",
			[&]() {
		if (gameState != nullptr) { gameState->getRenderer()->toggleHitboxes();};
	}));

	addItem(
		MenuItem("Quit",
			[&]() {
		StateManager::getInstance().switchToState(new TitleScreen(StateManager::getInstance().getWindow()));
	}));
}