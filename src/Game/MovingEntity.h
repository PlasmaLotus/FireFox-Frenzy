#pragma once

#ifndef __MOVING_ENTITY__
#define __MOVING_ENTITY__

#include "Entity.h"

#include <math.h>
#include <cmath>
class MovingEntity: public Entity {
public:

	MovingEntity();
	~MovingEntity();
	virtual void update(int32_t dt);
	virtual void handleCollision();
	virtual void handleCollision(Entity e);


};
#endif // !__MOVING_ENTITY__