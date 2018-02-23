#pragma once

#ifndef __CIRCLE_ENTITY__
#define __CIRCLE_ENTITY__

#include "MovingEntity.h"
class SquareEntity;
class CircleEntity : public MovingEntity {
public:

	//float prevPosX;
	//float prevPosY;
	//float prevPosZ;
	//float velocityX;
	//float velocityY;
	//float velocityZ;
	//Game * _game;
	float radius;
	CircleEntity();
	CircleEntity(float pX, float pY, float r);
	~CircleEntity();
	void update(int dt);
	//void update();
	bool testCollision(Entity e);
	bool testCollision(SquareEntity e);
	bool testCollision(CircleEntity e);
	virtual void handleCollision();

//protected:

};
#endif // !__MOVING_ENTITY__