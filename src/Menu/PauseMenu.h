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
	virtual void inputPause();
	virtual void inputBack();
private:
	GameState* gameState;
	//Menu* m_confirmMenu();

};

#endif