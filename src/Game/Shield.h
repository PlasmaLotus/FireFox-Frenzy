#pragma once

#ifndef __SHIELD_PROJECTILE__
#define __SHIELD_PROJECTILE__
#include "Projectile.h"


//enum PlayerState { ShootWindup, Shooting, ShootCooldown, Moving };
class Shield : public Projectile{
public:


	Shield(Player* pID);
	Shield();
	~Shield();
	void update(int32_t dt);
	void handleCollision();
	void handleCollision(Projectile p);
	

};
#endif // !__SHIELD_PROJECTILE__
