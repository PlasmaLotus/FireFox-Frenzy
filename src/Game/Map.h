#pragma once
#ifndef __Map__
#define __MAP__

#include "Entity.h"
#include <vector>
enum MapCollisionAngle { WallUp, WallDown, WallLeft, WallRight };
class Map: public Entity {
public:
	Map();
	Map(float wdth, float hght);
	~Map();
	virtual void update(int32_t dt);
	/*
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	*/
	virtual bool testCollision(Entity *e);
	std::vector<Entity*> _walls;

protected:
	/*
	virtual bool _testCollision(CircleEntity* e);
	virtual bool _testCollision(SquareEntity* e);
	virtual bool _testCollision(Entity* e);
	*/
	bool _testCollisionOuterWalls(Entity* e);
	bool _testCollisionWalls(Entity* e);
	void _handleCollisionOuterWall(Entity*e, MapCollisionAngle angle);
	void _handleCollisionWall(Entity*e, Entity wall, MapCollisionAngle angle);
	void generateMap(int generationID = 0);
};
#endif //Map