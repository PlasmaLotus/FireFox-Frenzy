#pragma once

#ifndef __ENTITY__
#define __ENTITY__
#include <stdint.h>
#include <vector>

struct  Vector2
{
	float x;
	float y;
};

struct CollisionStack {
	int _id;
	int delay;
};

class Entity {
public:
	int _id;
	float posX;
	float posY;
	float width;
	float height;
	float orientation;
	float prevPosX;
	float prevPosY;
	float velocityX;
	float velocityY;
	Entity();
	virtual ~Entity();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	int getID();
	bool isID(int id);
	virtual bool collidableWith(Entity e);
	virtual bool testCollision(Entity*e);
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	float _distanceBetween(float x, float y);
	float _distanceBetween(Vector2 v);
	float _distanceBetween(Entity e);

	float _angleBetween(float x, float y);
	float _angleBetween(Vector2 v);
	float _angleBetween(Entity e);
	std::vector<CollisionStack> _collisions;
	int _collisionDelay;
	int _hitlagFrames;
	bool _inHitlag;
	/*
	int _gridPosX;
	int _gridPosY;
	*/

protected:
	virtual bool testCollision(Entity e);

	bool _testVerticalCollision(Entity e);
	bool _testHorizontalCollision(Entity e);

};
#endif // !__ENTITY__
