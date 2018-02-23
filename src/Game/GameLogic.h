/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Game_Logic_
#define _Game_Logic_

#include "Player.h"
#include <stdint.h>

enum GameCurrentState{RUNNING, PAUSED, ENDED};

class GameLogic{
	
public:
	int frame = 0;
	int32_t dt;
	GameCurrentState gameState;

	GameLogic();
	~GameLogic();

	void reset();
	void tick();
	void pause();
	Player *getPlayer(int playerNumber);
	Player getPlayerCopy(int playerNumber);
	Player p1;
private:

	

};

#endif // !_Game_

