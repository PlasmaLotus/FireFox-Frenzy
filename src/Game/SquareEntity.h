#pragma once
#ifndef __MOVING_SQUARE_ENTITY__
#define __MOVING_SQUARE_ENTITY__

#include "Entity.h"
class CircleEntity;
class SquareEntity: public Entity {
public:
	SquareEntity();
	~SquareEntity();
	SquareEntity(float pX, float pY, float wdth, float hght);
	virtual void update(int32_t dt);
	virtual bool testCollision(Entity e);
	virtual bool testCollision(SquareEntity e);
	virtual bool testCollision(CircleEntity e);
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
};
#endif //