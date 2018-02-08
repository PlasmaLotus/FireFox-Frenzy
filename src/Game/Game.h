/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Game_
#define _Game_

#include "Player.h"

enum GameCurrentState{RUNNING, PAUSED, ENDED};

class Game{
	
public:
	int frame = 0;
	int dt;
	GameCurrentState gameState;

	Game();
	~Game();

	void reset();
	void tick();
	void pause();
	Player *getPlayer(int playerNumber);
	Player p1;
private:

	

};

#endif // !_Game_

