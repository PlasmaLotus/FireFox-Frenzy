#pragma once

#ifndef __MOVING_ENTITY__
#define __MOVING_ENTITY__

#include "Entity.h"
class MovingEntity: public Entity {
public:
	//float posX;
	//float posY;
	//float posZ;
	//float orientation;
	//float radianOrientation;

	float prevPosX;
	float prevPosY;
	float prevPosZ;
	float velocityX;
	float velocityY;
	float velocityZ;
	//Game * _game;
	MovingEntity();
	~MovingEntity();
	void update(int dt);
	//void update();


//protected:

};
#endif // !__MOVING_ENTITY__