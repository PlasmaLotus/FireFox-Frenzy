/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Game_
#define _Game_

//#include "../Main.h"

enum GameCurrentState{RUNNING, PAUSED, ENDED};

class Game{
	
public:
	int frame = 0;

	GameCurrentState gameState;
	Game();
	~Game();

	void reset();
	void tick();
	void pause();

private:

	

};

#endif // !_Game_

