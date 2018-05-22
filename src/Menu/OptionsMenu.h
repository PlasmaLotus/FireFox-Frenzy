/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#ifndef _OptionsMenu_
#define _OptionsMenu_
#include "Menu.h"

class GameState;
class OptionsMenu: public Menu {
public:
	OptionsMenu();
	
	virtual ~OptionsMenu();
	void tick(int dt);
	virtual void inputPause();
	virtual void inputBack();
private:
	GameState* gameState;
	//Menu* m_confirmMenu();

};

#endif