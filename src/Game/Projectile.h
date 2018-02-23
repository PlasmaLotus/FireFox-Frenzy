#pragma once

#ifndef __PROJECTILE__
#define __PROJECTILE__
#include <math.h>
#include "CircleEntity.h"

#include <cmath>
//enum PlayerState { ShootWindup, Shooting, ShootCooldown, Moving };
class Projectile : public CircleEntity {
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
	float orientationX;
	float orientationY;
	int durability;
	int lifetime;

	//Game * _game;
	Projectile();
	~Projectile();
	void update(int dt);

};
#endif // !__PLAYER__