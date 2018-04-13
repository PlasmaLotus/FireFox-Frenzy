#pragma once
#ifndef __SHIELD_PROJECTILE__
#define __SHIELD_PROJECTILE__
#include "Projectile.h"
class Player;
class Shield : public Projectile{
public:
	Shield(Player* pID);
	Shield();
	~Shield();
	void update(int32_t dt);
	void handleCollision();
	void handleCollision(Entity *e);
	Player* playerPtr;
};
#endif
