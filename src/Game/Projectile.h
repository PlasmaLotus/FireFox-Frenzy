#pragma once

#ifndef __PROJECTILE__
#define __PROJECTILE__
#include "CircleEntity.h"

class Player;
//enum PlayerState { ShootWindup, Shooting, ShootCooldown, Moving };
class Projectile : public CircleEntity {
public:
	int power;
	float orientationX;
	float orientationY;
	int durability;
	int lifetime;
	Projectile(Player* pID);
	Projectile();
	~Projectile();
	void update(int32_t dt);

	bool isAlive();
	bool collidableWith(Entity e);
	bool collidableWith(Projectile e);
	bool collidableWith(Player e);
	void handleCollision();
	void handleCollision(Projectile p);
	
	Player *playerPtr;
	Player* getPlayer();
	int getPlayerID();
};
#endif // !__PROJECTILE__