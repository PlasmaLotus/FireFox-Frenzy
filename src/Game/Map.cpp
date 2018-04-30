#include "SquareEntity.h"
#include "CircleEntity.h"
#include "GameLogic.h"
#include "Map.h"

Map::Map() :
	Map(GameLogic::MAP_DEFAULT_WIDTH, GameLogic::MAP_DEFAULT_HEIGHT)
{
}

Map::~Map(){
}

Map::Map(float wdth, float hght):
Entity(){
	width = wdth;
	height = hght;
	generateMap(1);
}

void Map::update(int32_t dt){
	//Entity::update(dt);
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
	//_handleCollisionWall()
	bool collision = false;
	/*
	for (int i = _walls.size() - 1; i >= 0; --i) {
		Entity &w{ _walls.at(i) };
		if (w.testCollision(e)) {
			//Determine where the collision should be handled//
			collision = true;

			//Test in X axis
			if (e->posX <= w.posX) {
				_handleCollisionWall(e, w, MapCollisionAngle::WallLeft);
			}
		}
	}
	*/
	if (e != nullptr) {
		for (int i = _walls.size() - 1; i >= 0; --i) {
			Entity &w{ _walls.at(i) };
			if (w.testCollision(e)) {
				/*Collision with wall*/

				if (e->posX - e->width / 2 < w.posX + w.width / 2) {
					collision = true;
					_handleCollisionWall(e, w, MapCollisionAngle::WallRight);
				}
				if (e->posX + e->width / 2 > w.posX - w.width / 2) {
					collision = true;
					_handleCollisionWall(e, w, MapCollisionAngle::WallLeft);
				}

				if (e->posY - e->height / 2 < w.posY + w.height / 2) {
					collision = true;
					_handleCollisionWall(e, w, MapCollisionAngle::WallDown);
				}
				if (e->posY + e->height / 2 > w.posY - w.height / 2) {
					collision = true;
					_handleCollisionWall(e, w, MapCollisionAngle::WallUp);
				}
			}
		}
	}


	return collision;
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
		offset = this->width - e->posX - e->width /2;
		e->posX += offset;
		/*
		//Warps to opposite wall
		offset = e->width / 2 - this->width - e->posX;
		e->posX += offset;
		*/
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
		offset = this->height - e->posY - e->height / 2;
		e->posY += offset;
		/*
		//Warps to opposite wall
		offset = e->height / 2 - this->height - e->posY;
		e->posY += offset;
		*/
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


void Map::generateMap(int generationID) {
	/*Generate map dimensions and obstacles*/;

	switch (generationID) {
	case 1: {
		/*
		SquareEntity* s{ new SquareEntity(700, 700, 100, 100) };
		_walls.push_back(dynamic_cast<Entity*>(s));
		*/
		_walls.push_back(SquareEntity(700, 700, 100, 100));
		break;
		}
	default: break;
	}
}