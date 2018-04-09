/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

/*Under Construction*/
#ifndef _Menu_
#define _Menu_
#include <vector>
#include "SFML\Graphics.hpp"
#include "MenuItem.h"

class Menu {
public:

	//Menu();
	Menu();
	virtual ~Menu();
	virtual void tick();
	virtual void handleInput();
	virtual void inputLeft();
	virtual void inputRight();
	virtual void inputUp();
	virtual void inputDown();
	virtual void inputSelect();
	virtual void inputBack();
	//virtual virtual ~Menu();

	sf::RenderWindow *window;
	int selection;
	std::vector<MenuItem> items;
	Menu *previousMenu;
	Menu *nextMenu;
	void setPreviousMenu(Menu* menu);
	void addItem(MenuItem menuItem);

	void onSelection();

	void onItemIncrease();

	void onItemDecrease();

	//void onItemSelect();

	void onItemChange();

	void onReturn();

};

#endif
