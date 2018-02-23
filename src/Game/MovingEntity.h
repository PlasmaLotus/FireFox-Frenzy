#pragma once

#ifndef __MOVING_ENTITY__
#define __MOVING_ENTITY__

#include "Entity.h"



class MovingEntity: public Entity {
public:

	float prevPosX;
	float prevPosY;
	float prevPosZ;
	//float prevPosZ;
	float velocityX;
	float velocityY;
	//float velocityZ;
	//Game * _game;
	MovingEntity();
	~MovingEntity();
	virtual void update(int dt);
	//void update();


//protected:

};
#endif // !__MOVING_ENTITY__