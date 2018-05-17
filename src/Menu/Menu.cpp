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
	if (selection < 0) {
		selection = items.size() - 1;
	}
	if (_inputted) {
		_inputTime += dt;
	}
	else {
		_inputTime = 0;
	}
	_inputted = false;
}

void Menu::inputLeft()
{
	input();
	if (items.size() >= selection) {

	printf("Input left\n");
	if (items.at(selection).menuItemType == MenuItemType::RANGE) {
		items.at(selection).decrease();
	}
	onItemDecrease();
	}
}

void Menu::inputRight()
{
	input();
	if (items.size() >= selection) {

	printf("Input right\n");
	if (items.at(selection).menuItemType == MenuItemType::RANGE || items.at(selection).menuItemType == MenuItemType::LIST) {
		items.at(selection).increase();
		onItemIncrease();
	}
	}
}

void Menu::inputUp()
{
	input();
	selection-= 1;
	if (selection < 0) {
		selection = items.size() - 1;
	}
	onItemChange();
}

void Menu::inputDown()
{
	input();
	selection+= 1;
	if (selection >= items.size()) {
		selection = 0;
	}
	onItemChange();
}

void Menu::inputSelect()
{
	input();
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

void Menu::inputBack() {
	input();
	printf("Input back\n");
	onReturn();
	StateManager::getInstance().goBack();
}
void Menu::inputPause(){
	inputSelect();
}
std::vector<MenuItem> & Menu::getItems()
{
	return items;
}
int Menu::getSelection()
{
	return selection;
}
void Menu::input(){
	_inputted = true;
}

int Menu::getItemsSize() {
	return items.size();
}
MenuItem Menu::getItem(int index)
{
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