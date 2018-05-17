#include "PauseMenu.h"
#include "../States/StateManager.h"
#include "../States/TitleScreen.h"
#include "../States/GameState.h"

PauseMenu::PauseMenu():
	Menu(){
	addItem(
		MenuItem("Back To Game",
			[&]() {
		StateManager::getInstance().goBack();
	}));

	addItem(
		MenuItem("Back to Title",
			[&]() {
		StateManager::getInstance().goBackToTitle();
	}));

	addItem(
		MenuItem("Quit",
			[&]() {
		StateManager::getInstance().switchToState(new TitleScreen(StateManager::getInstance().getWindow()));
	}));
}


PauseMenu::PauseMenu(GameState* gs):
	Menu(),
	gameState{ gs } {
	addItem(
		MenuItem("Back To Game",
			[&]() {
		if (gameState != nullptr) {
			gameState->pause();
		}
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
		MenuItem("Back to Title",
			[&]() {
		StateManager::getInstance().goBackToTitle();
	}));

	addItem(
		MenuItem("Quit",
			[&]() {
		StateManager::getInstance().quit();
	}));
}

PauseMenu::~PauseMenu() {
}

void PauseMenu::inputBack()
{
	input();
	onReturn();
	if (gameState != nullptr) {
		gameState->pause(); 
	}
}

void PauseMenu::inputPause() {
	inputBack();
}