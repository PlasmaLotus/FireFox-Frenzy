#pragma once
#ifndef __Map__
#define __MAP__

#include "Entity.h"
#include "SquareEntity.h"
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
	Vector2 getRandomSpawnPoint(float width, float height);
	Vector2 getRandomSpawnPointFrom(float x, float y, float maxDistance, float width, float height);
	int _mapGenID;
	Vector2 getSpawnPoint(int player);
	void generateMap(int generationID = 0);
protected:
	/*
	virtual bool _testCollision(CircleEntity* e);
	virtual bool _testCollision(SquareEntity* e);
	virtual bool _testCollision(Entity* e);
	*/
	void clearWalls();
	bool _testCollisionOuterWalls(Entity* e);
	bool _testCollisionWalls(Entity* e);
	void _handleCollisionOuterWall(Entity*e, MapCollisionAngle angle);
	void _handleCollisionWall(Entity*e, Entity wall, MapCollisionAngle angle);


};
#endif //Map