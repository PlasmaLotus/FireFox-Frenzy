#include "OptionsMenu.h"
#include "../States/StateManager.h"
#include "../States/TitleScreen.h"

OptionsMenu::OptionsMenu():
	Menu(){

	addItem(
		MenuItem("Volume",
			[&]() {
		StateManager::getInstance().audioEventManager.getVolume();
	}, StateManager::getInstance().audioEventManager.getVolume(), 100, MenuItemType::RANGE));


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

	StateManager::getInstance().audioEventManager.setVolume(items.at(0).getRangeValue());
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