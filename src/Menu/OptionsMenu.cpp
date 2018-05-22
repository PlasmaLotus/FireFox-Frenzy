#include "OptionsMenu.h"
#include "../States/StateManager.h"
#include "../States/TitleScreen.h"

OptionsMenu::OptionsMenu():
	Menu(){

	addItem(
		MenuItem("Toggle FPS",
			[&]() {
		StateManager::getInstance().toggleFPS();
	}));

	addItem(
		MenuItem("Toggle Hitboxes",
			[&]() {
		StateManager::getInstance().toggleHitboxes();
	}));

	addItem(
		MenuItem("Toggle Player Positions ",
			[&]() {
		StateManager::getInstance().togglePositions(); 
	}));

	addItem(
		MenuItem("Back",
			[&]() {
		StateManager::getInstance().goBack();
	}));
}


OptionsMenu::~OptionsMenu() {
}

void OptionsMenu::tick(int dt)
{
	Menu::tick(dt);
}

void OptionsMenu::inputBack()
{
	input();
	onReturn();
	StateManager::getInstance().goBack();
}

void OptionsMenu::inputPause() {
	inputSelect();
}