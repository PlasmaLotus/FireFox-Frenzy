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
	virtual void inputLeft();
	virtual void inputRight();
	virtual void inputUp();
	virtual void inputDown();
	virtual void inputSelect();
	virtual void inputBack();

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
	virtual void onItemChange();
	virtual void onReturn();
};

#endif
