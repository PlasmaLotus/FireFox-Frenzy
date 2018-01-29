#pragma once
/*
Created by PlasmaLotus
Updated May 17, 2017
*/

#include "Menu.h"

//#include "MenuItem.h"


#ifndef __MainMenu__
#define __MainMenu__

class MainMenu : public Menu {
public:
	MainMenu();
	//MainMenu(sf::RenderWindow* w, Menu *pm);
	~MainMenu();
	//sf::RenderWindow *window;
	//void inputSelect();
};

#endif