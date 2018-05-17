/*
Created by PlasmaLotus
Updated Mai 14, 2016
*/

#ifndef _EndGamePauseMenu_
#define _EndGamePauseMenu_
#include "Menu.h"

class GameState;
class EndGamePauseMenu : public Menu {
public:
	EndGamePauseMenu();
	EndGamePauseMenu(GameState *gs);
	virtual ~EndGamePauseMenu();
	virtual void inputPause();
	virtual void inputBack();
private:
	GameState* gameState;
	//Menu* m_confirmMenu();
};

#endif