/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

/*Under Construction*/

#include <vector>
#include "SFML\Graphics.hpp"
#include "MenuItem.h"

#ifndef _Menu_
#define _Menu_


class Menu {
public:

	//Menu();
	Menu();
	virtual ~Menu();
	virtual void tick();
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

	virtual void onSelection();

	virtual void onItemIncrease();

	virtual void onItemDecrease();

	//void onItemSelect();

	virtual void onItemChange();

	virtual void onReturn();

};

#endif
