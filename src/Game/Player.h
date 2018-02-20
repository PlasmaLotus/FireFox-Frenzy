#pragma once

#ifndef __PLAYER__
#define __PLAYER__
#include <math.h>
#include "MovingEntity.h"
#include "Projectile.h"
#include <vector>
#include <cmath>
enum PlayerState{ ShootWindup, Shooting, ShootCooldown, Moving, Dashing};
class Player: public MovingEntity {
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
	float cursorOrientation;
	float cursorOrientationX;
	float cursorOrientationY;


	//Game * _game;
	Player();
	~Player();
	void update(int dt);
	PlayerState state;
	void shoot();
	void dash();
	std::vector <Projectile> projectiles;
	//void update();
	void setPlayerOrienation(float x, float y);
	void setCursorOrientation(float x, float y);

	void setCursorOrientationFromMouse(int x, int y);
	
	
	int const SHOOT_COOLDOWN {10};
	bool shootHeld{ false };
	int shootTime{ 0 };
	bool canShoot{ true };

	float dashVelocity;
	int dashMaxDuration;
	int dashTime;
	float dashOrientation;
	float dashOrientationX;
	float dashOrientationY;

	//protected:

};
#endif // !__PLAYER__