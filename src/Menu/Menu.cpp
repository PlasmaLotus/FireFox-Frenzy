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

Menu::Menu()
{
	selection = 0;
}

void Menu::tick()
{
	if (selection < 0) {
		selection = items.size() - 1;
	}
}

void Menu::inputLeft()
{
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
	if (items.size() >= selection) {

	printf("Input right\n");
	if (items.at(selection).menuItemType == MenuItemType::RANGE) {
		items.at(selection).increase();
	}
	onItemIncrease();
	}
}

void Menu::inputUp()
{

	printf("Input up\n");
	selection-= 1;
	if (selection < 0) {
		selection = items.size() - 1;
	}

	onItemChange();
}

void Menu::inputDown()
{
	printf("Input down\n");
	selection+= 1;
	if (selection >= items.size()) {
		selection = 0;
	}

	onItemChange();
}

void Menu::inputSelect()
{
	printf("Input select\n");
	if (selection >= 0 && selection < items.size()) {
		items.at(selection).getOptionString();
		items.at(selection).getFn()();
	}
	else {
		printf("Cant Select that");
	}
	onSelection();
	
}

void Menu::inputBack() {
	printf("Input back\n");
	onReturn();
	StateManager::getInstance().goBack();
}
/*
void Menu::setPreviousMenu(Menu* menu){
	previousMenu = menu;
}
*/
void Menu::addItem(MenuItem menuItem) {
	items.push_back(menuItem);
}

void Menu::onSelection() {

}
void Menu::onItemIncrease() {

}
void Menu::onItemDecrease() {

}

void Menu::onItemChange() {

}

void Menu::onReturn() {

}