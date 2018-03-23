#pragma once

#ifndef __PROJECTILE__
#define __PROJECTILE__
#include "CircleEntity.h"

class Player;
//enum PlayerState { ShootWindup, Shooting, ShootCooldown, Moving };
class Projectile : public CircleEntity {
public:
	
	float orientationX;
	float orientationY;
	int durability;
	int lifetime;
	Projectile(Player* pID);
	Projectile();
	~Projectile();
	void update(int32_t dt);
	bool isAlive();
	int power;
	void handleCollision();
	void handleCollision(Entity *e);
	bool collidableWith(Entity e);
	bool collidableWith(Projectile e);
	bool collidableWith(Player e);


	Player *playerPtr;
	Player* getPlayer();
	int getPlayerID();
};
#endif // !__PROJECTILE__