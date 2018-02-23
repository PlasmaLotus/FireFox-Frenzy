#pragma once

#ifndef __MOVING_SQUARE_ENTITY__
#define __MOVING_SQUARE_ENTITY__

#include "MovingEntity.h"
class CircleEntity;
class SquareEntity: public MovingEntity {
public:

	//float prevPosX;
	//float prevPosY;
	//float prevPosZ;
	//float velocityX;
	//float velocityY;
	//float velocityZ;
	//Game * _game;
	float width;
	float height;
	SquareEntity();
	~SquareEntity();
	SquareEntity(float pX, float pY, float wdth, float hght);
	void update(int dt);
	//void update();
	bool testCollision(Entity e);
	bool testCollision(SquareEntity e);
	bool testCollision(CircleEntity e);
	virtual void handleCollision();
	Vector2 distanceBetweenCenter(Entity e);
	Vector2 angleBetweenCenter(Entity e);

//protected:

};
#endif // !__MOVING_ENTITY__