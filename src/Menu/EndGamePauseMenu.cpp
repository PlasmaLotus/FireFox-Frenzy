#include "EndGamePauseMenu.h"
#include "../States/StateManager.h"
#include "../States/TitleScreen.h"
#include "../States/GameState.h"

EndGamePauseMenu::EndGamePauseMenu():
	Menu(){
	
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


EndGamePauseMenu::EndGamePauseMenu(GameState* gs):
	Menu(),
	gameState{ gs } {
	addItem(
		MenuItem("Play Again!",
			[&]() {
		if (gameState != nullptr) {
			gameState->reset();
		}
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

EndGamePauseMenu::~EndGamePauseMenu() {
}

void EndGamePauseMenu::inputBack()
{
	input();
	onReturn();
	if (gameState != nullptr) {
		gameState->pause(); 
	}
}

void EndGamePauseMenu::inputPause() {
	inputBack();
}