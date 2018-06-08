#pragma once

#ifndef __ENTITY__
#define __ENTITY__
#include <stdint.h>
#include <vector>

struct  Vector2
{
	//Vector2(float i, float j) { x = i, y = j };
	float x;
	float y;
	Vector2():x(0), y(0){}
	Vector2(float _x, float _y) :x(_x), y(_y) {};
	float getMagnitude() { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); };
	Vector2 getNormal(){ 
		if (getMagnitude() > 0) {
			return Vector2(x / getMagnitude(), y / getMagnitude());
		}
		else {
			return Vector2(0.f, 0.f);
		}
	}
};

struct RGBA {
	int r, g, b, a;
	RGBA(int _r, int _g, int _b, int _a) :r(_r), g(_g), b(_b), a(_a) {};
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
	//float velocity;

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

protected:
	virtual bool testCollision(Entity e);

	bool _testVerticalCollision(Entity e);
	bool _testHorizontalCollision(Entity e);

};
#endif // !__ENTITY__
