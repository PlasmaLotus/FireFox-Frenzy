#pragma once

#ifndef __PLAYER__
#define __PLAYER__

#include "MovingEntity.h"
class Player: public MovingEntity {
public:
	//float posX;
	//float posY;
	//float posZ;
	//float orientation;
	//float radianOrientation;
	//float prevPosX;
	//float prevPosY;
	//float prevPosZ;
	//float velocityX;
	//float velocityY;
	//float velocityZ;
	float cursorOrientation;
	//Game * _game;
	Player();
	~Player();
	void update(int dt);
	//void update();
	void setPlayerOrienation(float x, float y);
	void setCursorOrientation(float x, float y);


	//protected:

};
#endif // !__PLAYER__