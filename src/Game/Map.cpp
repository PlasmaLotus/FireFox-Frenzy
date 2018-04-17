#include "SquareEntity.h"
#include "CircleEntity.h"
#include "GameLogic.h"
#include "Map.h"

Map::Map() :
	Map(GameLogic::ENTITY_MINIMUM_WIDTH, GameLogic::ENTITY_MINIMUM_HEIGHT)
{
}

Map::~Map(){
}

Map::Map(float wdth, float hght):
Entity(){
	width = wdth;
	height = hght;
}

void Map::update(int32_t dt){
	//Entity::update(dt);
}

/*Return false if no collision*/
bool Map::_testCollision(Entity* e) {
	return false;
	//return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}

bool Map::_testCollision(SquareEntity* e) {
	return false;
	//return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}
bool Map::_testCollision(CircleEntity* e) {
	return false;
	/*
	Vector2 v1{ posX - width / 2, posY - height / 2 };
	Vector2 v2{ posX - width / 2, posY + height / 2 };
	Vector2 v3{ posX + width / 2, posY + height / 2 };
	Vector2 v4{ posX + width / 2, posY - height / 2 };
	return (e._distanceBetween(v1) <= e.width || e._distanceBetween(v2) <= e.width ||
		e._distanceBetween(v3) <= e.width || e._distanceBetween(v4) <= e.width);
	*/
}

bool Map::testCollision(Entity * e)
{
	bool collision = false;
	if (e != nullptr) {
		/*
		CircleEntity* ce = dynamic_cast<CircleEntity*>(e);
		SquareEntity* se = dynamic_cast<SquareEntity*>(e);
		if (ce != nullptr) {
			return testCollision(ce);
		}
		else if (se != nullptr) {
			return testCollision(se);
		}
		else {
			return testCollision(e);
		}
		*/
		if (_testCollisionOuterWalls(e)) {
			collision = true;
		}
		if (_testCollisionWalls(e)) {
			collision = true;
		}

		return collision;
	}
	else
		return false;
}

bool Map::_testCollisionOuterWalls(Entity * e){
	bool collision = false;
	/*Test up wall*/
	if (e != nullptr) {
		if (e->posX - e->width / 2 < 0) {
			collision = true;
			_handleCollisionOuterWall(e, MapCollisionAngle::WallLeft);
		}
		if (e->posX + e->width / 2 > this->width) {
			collision = true;
			_handleCollisionOuterWall(e, MapCollisionAngle::WallRight);
		}

		if (e->posY - e->height / 2 < 0) {
			collision = true;
			_handleCollisionOuterWall(e, MapCollisionAngle::WallUp);
		}
		if (e->posY + e->height / 2 > this->height) {
			collision = true;
			_handleCollisionOuterWall(e, MapCollisionAngle::WallDown);
		}
	}

	return collision;
}

bool Map::_testCollisionWalls(Entity * e){
	return false;
	//_handleCollisionWall()
}

void Map::_handleCollisionOuterWall(Entity * e, MapCollisionAngle angle){
	float offset;
	switch (angle) {
	case MapCollisionAngle::WallLeft:
	{
		offset = e->width/2 - e->posX;
		e->posX += offset;
		break;
	}
	case MapCollisionAngle::WallRight:
	{
		offset = e->width / 2 - this->width - e->posX;
		e->posX -= offset;
		break;
	}
	case MapCollisionAngle::WallUp:
	{
		offset = e->height / 2 - e->posY;
		e->posY += offset;
		break;
	}
	case MapCollisionAngle::WallDown:
	{
		offset = e->height / 2 - this->height - e->posY;
		e->posY -= offset;
		break;
	}
	default:break;
	}
}

void Map::_handleCollisionWall(Entity * e, Entity wall, MapCollisionAngle angle){
	float offset;
	/*Total potential width - distance*/
	switch (angle) {
	case MapCollisionAngle::WallLeft:
	{
		offset = (wall.width / 2 + e->width / 2) - (wall.posX  - e->posX);
		e->posX -= offset;
		break;
	}
	case MapCollisionAngle::WallRight:
	{
		offset = (wall.width/2 + e->width/2) - (e->posX - wall.posX);
		e->posX += offset;
		break;
	}
	case MapCollisionAngle::WallUp:
	{
		offset = (wall.width / 2 + e->width / 2) - (wall.posX - e->posX);
		e->posY -= offset;
		break;
	}
	case MapCollisionAngle::WallDown:
	{
		offset = (wall.width / 2 + e->width / 2) - (e->posX - wall.posX);
		e->posY += offset;
		break;
	}
	default:break;
	}
}
