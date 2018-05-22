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
	virtual void tick(int dt);
	virtual void inputLeft();
	virtual void inputRight();
	virtual void inputUp();
	virtual void inputDown();
	virtual void inputSelect();
	virtual void inputBack();
	virtual void inputPause();
	std::vector<MenuItem> & getItems();
	int getSelection();
	int getItemsSize();
	MenuItem getItem(int index);
protected:
	std::vector<MenuItem> items;
	virtual void input();
	int selection;
	void addItem(MenuItem menuItem);
	virtual void onSelection();
	virtual void onSelectionError();
	virtual void onItemIncrease();
	virtual void onItemDecrease();
	virtual void onItemChange();
	virtual void onReturn();
	bool _inputted;
	int _inputTime;
	static const int INPUT_INITIAL_DELAY{ 400 };
	static const int INPUT_INCRIMENTAL_DELAY{ 20 };
};

#endif
