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
	float posZ;
	float width;
	float height;
	float orientation;
	float prevPosX;
	float prevPosY;
	//float prevPosZ;
	float velocityX;
	float velocityY;
	//Game * _game;
	Entity();
	~Entity();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	int getID();
	bool isID(int id);
	virtual bool collidableWith(Entity e);
	virtual bool testCollision(Entity e);
	virtual void handleCollision();
	virtual void handleCollision(Entity e);
	virtual void handleCollision(Entity *e);
	float _distanceBetween(float x, float y);
	float _distanceBetween(Vector2 v);
	float _distanceBetween(Entity e);
	std::vector<CollisionStack> _collisions;
protected:
	bool _testVerticalCollision(Entity e);
	bool _testHorizontalCollision(Entity e);

};
#endif // !__ENTITY__
