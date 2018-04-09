#pragma once

#ifndef __PROJECTILE__
#define __PROJECTILE__
#include "CircleEntity.h"
#include <vector>
class Player;
//enum PlayerState { ShootWindup, Shooting, ShootCooldown, Moving };
class Projectile : public CircleEntity {
public:
	
	float orientationX;
	float orientationY;
	int durability;
	int lifetime;
	int power;
	Projectile(Player* pID);
	Projectile();
	virtual ~Projectile();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	bool collidableWith(Entity e);
	bool collidableWith(Projectile e);
	bool collidableWith(Player e);


	Player *playerPtr;
	Player* getPlayer();
	int getPlayerID();
};
#endif // !__PROJECTILE__