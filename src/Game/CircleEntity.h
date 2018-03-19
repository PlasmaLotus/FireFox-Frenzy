#pragma once

#ifndef __CIRCLE_ENTITY__
#define __CIRCLE_ENTITY__

#include "Entity.h"
class SquareEntity;
class CircleEntity : public Entity {
public:

	CircleEntity();
	CircleEntity(float pX, float pY, float r);
	~CircleEntity();
	virtual void update(int32_t dt);
	virtual bool testCollision(Entity e);
	virtual bool testCollision(SquareEntity e);
	virtual bool testCollision(CircleEntity e);
	virtual void handleCollision();
	virtual void handleCollision(Entity e);
	
//protected:

};
#endif // !__MOVING_ENTITY__