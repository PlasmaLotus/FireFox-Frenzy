#pragma once

#ifndef __PROJECTILE__
#define __PROJECTILE__
#include "CircleEntity.h"
#include "Item.h"
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
	Projectile(int pID);
	Projectile();
	Projectile(int pID, float x, float y);
	virtual ~Projectile();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollisionMap();
	virtual void handleCollision(Entity *e);
	virtual bool testCollision(Entity * e);
	int getPlayerID();
	int _playerID;
protected:
	bool collidableWith(Player* e);
	bool collidableWith(Projectile* e);
	bool collidableWith(Entity* e);
	bool collidableWith(Item* e);
	/*
	virtual bool testCollision(CircleEntity e);
	virtual bool testCollision(SquareEntity e);
	virtual bool testCollision(Entity e);
	*/
};
#endif // !__PROJECTILE__