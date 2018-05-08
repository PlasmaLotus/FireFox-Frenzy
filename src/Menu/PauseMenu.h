/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#ifndef _PauseMenu_
#define _PauseMenu_
#include "Menu.h"

class GameState;
class PauseMenu: public Menu {
public:
	PauseMenu();
	PauseMenu(GameState *gs);
	virtual ~PauseMenu();
	
private:
	GameState* gameState;
};

#endif