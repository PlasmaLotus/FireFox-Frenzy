#include "Menu.h"
#include "../States/StateManager.h"


/*Under Construction*/

Menu::~Menu()
{
	//window->create(sf::VideoMode(800, 600), "TACD");
	//delete previousMenu;
	//delete nextMenu;
	items.clear();
}

Menu::Menu() :
	selection(0),
	_inputted(false),
	_inputTime(0)
{
}

void Menu::tick(int dt)
{
	while (selection < 0) {
		selection += items.size();
	}
	
	while (selection >= items.size()) {
		selection -= items.size();
	}
	

	if (_inputted) {
		_inputTime += dt;
		if (_inputTime > INPUT_INITIAL_DELAY) {
			_inputTime -= INPUT_INCRIMENTAL_DELAY;
		}
	}
	else {
		_inputTime = 0;
	}
	_inputted = false;
}

void Menu::input() {
	_inputted = true;
}

void Menu::inputLeft()
{
	if (_inputTime == 0 || _inputTime >= INPUT_INITIAL_DELAY ) {
		if (!_inputted) {
			if (items.size() >= selection) {
				if (items.at(selection).getMenuType() == MenuItemType::RANGE) {
					items.at(selection).decrease();
					onItemDecrease();
				}
			}
		}
	}
	input();
}

void Menu::inputRight()
{
	if (_inputTime == 0 || _inputTime >= INPUT_INITIAL_DELAY) {
		if (!_inputted) {
			if (items.size() >= selection) {
				if (items.at(selection).getMenuType() == MenuItemType::RANGE || items.at(selection).getMenuType() == MenuItemType::LIST) {
					items.at(selection).increase();
					onItemIncrease();
				}
			}
		}
	}
	input();
}

void Menu::inputUp()
{
	if (_inputTime == 0 || _inputTime >= INPUT_INITIAL_DELAY){
		if (!_inputted) {
			selection -= 1;
			/*
			if (selection < 0) {
				selection = items.size() - 1;
			}
			*/
			onItemChange();
		}
	}
	input();
}

void Menu::inputDown()
{
	if (_inputTime == 0 || _inputTime >= INPUT_INITIAL_DELAY) {
		if (!_inputted) {
			selection+= 1;
		/*
		if (selection >= items.size()) {
			selection = 0;
		}
		*/
			onItemChange();
		}
	}
	input();
}

void Menu::inputSelect()
{
	if (_inputTime == 0 || _inputTime >= INPUT_INITIAL_DELAY) {
		if (!_inputted) {
			if (selection >= 0 && selection < items.size()) {
				items.at(selection).getOptionString();
				items.at(selection).getFn()();
				onSelection();
			}
			else {
				printf("Cant Select that");
				onSelectionError();
			}
		}
		
	}
	
	input();
}

void Menu::inputBack() {
	if (_inputTime == 0 || _inputTime >= INPUT_INITIAL_DELAY || !_inputted) {
		onReturn();
		StateManager::getInstance().goBack();
	}
	input();
	//printf("Input back\n");
}
void Menu::inputPause(){
	inputSelect();
}
std::vector<MenuItem> & Menu::getItems(){
	return items;
}
int Menu::getSelection(){
	return selection;
}

int Menu::getItemsSize() {
	return items.size();
}
MenuItem Menu::getItem(int index){
	if (index < 0) {
		index = 0;
	}
	else if (index >= items.size()) {
		index = items.size() - 1;
	}
	return items.at(index);
}
void Menu::addItem(MenuItem menuItem) {
	items.push_back(menuItem);
}

void Menu::onSelection() {
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::MenuSelection));
}
void Menu::onSelectionError(){
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::MenuSelectionError));
}
void Menu::onItemIncrease() {
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::MenuItemIncrease));
}
void Menu::onItemDecrease() {
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::MenuItemDecrease));
}

void Menu::onItemChange() {
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::MenuItemChange));
}

void Menu::onReturn() {
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::MenuReturn));
}