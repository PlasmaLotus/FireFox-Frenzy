#include "SquareEntity.h"
#include "CircleEntity.h"
#include "GameLogic.h"
#include "Map.h"
#include <random>

Map::Map() :
	Map(GameLogic::MAP_DEFAULT_WIDTH, GameLogic::MAP_DEFAULT_HEIGHT)
{
}

Map::~Map(){
	clearWalls();
}

Map::Map(float wdth, float hght):
Entity()
{
	_mapGenID = 0;
	width = wdth;
	height = hght;
	generateMap(1);
}

void Map::update(int32_t dt){
	//Entity::update(dt);
}

bool Map::testCollision(Entity * e){
	bool collision = false;
	if (e != nullptr) {
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

void Map::clearWalls()
{
	for (int i = _walls.size() - 1; i >= 0; --i) {
		Entity* wall{ _walls.at(i) };
		if (wall != nullptr) {
			delete wall;
		}
	}
	_walls.clear();
}

bool Map::_testCollisionOuterWalls(Entity * e) {
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

	Projectile * p = dynamic_cast<Projectile*>(e);
	if (p != nullptr) {
		if (collision) {
			p->handleCollisionMap();

		}
	}
	if (collision) {
		e->handleCollision(this);
	}
	return collision;
}

bool Map::_testCollisionWalls(Entity * e){
	bool collision = false;
	
	if (e != nullptr) {
		int e_x = e->posX / 100;
		int e_y = e->posY / 100;

		for (int i = _walls.size() - 1; i >= 0; --i) {
			Entity* w{ _walls.at(i) };
			if (w != nullptr) {
				int w_x = w->posX / 100;
				int w_y = w->posY / 100;
				int w_wid = w->width / 100;
				int w_hei = w->height / 100;
				if (std::abs(e_x - w_x) < w_wid + 2 && std::abs(e_y - w_y) < w_hei + 2 ) {
					if (w->testCollision(e)) {
						collision = true;
						CircleEntity * cw = dynamic_cast<CircleEntity*>(w);
						SquareEntity * sw = dynamic_cast<SquareEntity*>(w);
				
						if (sw != nullptr) {
							/*Testing with square walls*/
							//Testing if the object entered from the right
							float widthSum = e->width / 2 + w->width / 2;
							float heightSum = e->height / 2 + w->height / 2;
							float arbitraryPixel = 0.001f; //Small unit of msure to make sure the object isnt still colliding with the wall the next frame
							if (e->posX >= w->posX) {
								//On the right of the wall
								if (e->prevPosX - w->posX > widthSum) {
									//The entity was not already within the projected X axis
									if (e->posX - w->posX < widthSum) {
										float insertX = widthSum - (e->posX - w->posX);
										e->posX += insertX + arbitraryPixel;
									}
								}
							}
							else {
								//On the left of the wall
								/**/
								if (w->posX - e->prevPosX > widthSum) {
									//The entity was not already within the projected X axis
									if (w->posX - e->posX < widthSum) {
										float insertX = (w->posX - e->posX) - widthSum;
										e->posX += insertX - arbitraryPixel;
									}
								}
							}

							//Testing if the object entered from the bottom
							if (e->posY >= w->posY) {
								//On the bottom of the wall
								if (e->prevPosY - w->posY > heightSum) {
									//The entity was not already within the projected X axis
									if (e->posY - w->posY < heightSum) {
										float insertY = heightSum - (e->posY - w->posY);
										e->posY += insertY + arbitraryPixel;
									}
								}
							}
							else {
								//On the top of the wall
								if (w->posY - e->prevPosY > heightSum) {
									//The entity was not already within the projected X axis
									if (w->posY - e->posY < heightSum) {
										float insertY = (w->posY - e->posY) - heightSum;
										e->posY += insertY - arbitraryPixel;
									}
								}
							}
						}
						else if (cw != nullptr) {
							/*Testing with a Circle Obstacle*/
							/*X: cos, y = sin*/
							//float angleBetween = std::atan2(e->posY - cw->posY, e->posX - cw->posX);//rad
							float angleBetween = e->_angleBetween(cw->posX, cw->posY);
							float widthWall = std::abs(cw->width / 2 * cos(angleBetween));
							float heightWall = std::abs(cw->height / 2 * sin(angleBetween));
							float widthEntity = std::abs(e->width / 2 * cos(angleBetween));
							float heightEntity = std::abs(e->height / 2 * sin(angleBetween));

							float totalWidth = std::abs(e->width/2 * cos(angleBetween)) + std::abs(cw->width/2 * cos(angleBetween));
							float totalHeight = std::abs(e->height/2 * sin(angleBetween)) + std::abs(cw->height/2 * sin(angleBetween));

							float widthBetween = std::pow(std::pow(std::abs(totalWidth), 2) + std::pow(std::abs(totalHeight), 2), 0.5);
							float arbitraryPixel = 0.001f; //Small unit of msure to make sure the object isnt still colliding with the wall the next frame
							if (widthBetween > e->_distanceBetween(w->posX, w->posY)) {
								//circle collision = true;
								if (e->posX >= w->posX) {
									//On the right of the wall
									float insertX = (widthWall+ widthEntity) - (e->posX - w->posX);
									e->posX += insertX + arbitraryPixel;
								}
								else {
									//On the left of the wall
									float insertX = (w->posX - e->posX) - (widthWall + widthEntity);
									e->posX += insertX - arbitraryPixel;
								}
								//Testing if the object entered from the bottom
								if (e->posY >= w->posY) {
									//On the bottom of the wall
									float insertY = (heightWall + heightEntity) - (e->posY - w->posY);
									e->posY += insertY + arbitraryPixel;
								}
								else {
									//On the top of the wall
									float insertY = (w->posY - e->posY) - (heightWall + heightEntity);
									e->posY += insertY - arbitraryPixel;
								}

							}
						}
						else {
							/*If the wall isnt a square or circle entity...*/
						}
						e->handleCollision(w);
					}
				}
			}
		}

		Projectile * p = dynamic_cast<Projectile*>(e);
		if (p != nullptr) {
			if (collision) {
				p->handleCollisionMap();

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
		if (e->velocityX < 0) {
			//e->velocityX = 0;
		}
		break;
	}
	case MapCollisionAngle::WallRight:
	{
		offset = this->width - e->posX - e->width /2;
		e->posX += offset;
		if (e->velocityX > 0) {
			//e->velocityX = 0;
		}
		
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

		if (e->velocityY < 0) {
			//e->velocityY = 0;
		}
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
		if (e->velocityY > 0) {
			//e->velocityY = 0;
		}
		break;
	}
	default:break;
	}
	//e->handleCollision(this);
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
	_mapGenID = generationID;
	clearWalls();
	switch (generationID) {
	case 0: {
		//Test 
		width = 4096.f;
		height = 2160.f;
		_walls.push_back(new SquareEntity(700, 700, 100, 100));
		_walls.push_back(new CircleEntity(900, 900, 100));
		break;
	}
	case 1: {

		width = 4096.f;
		height = 2160.f;
		_walls.push_back(new SquareEntity(width / 4.f, height / 4.f, width / 10.f, height / 10.f));
		_walls.push_back(new SquareEntity(width / 4.f * 3.f, height / 4.f, width / 10.f, height / 10.f));
		_walls.push_back(new SquareEntity(width / 4.f, height / 4.f * 3.f, width / 10.f, height / 10.f));
		_walls.push_back(new SquareEntity(width / 4.f * 3.f, height / 4.f * 3.f, width / 10.f, height / 10.f));
		_walls.push_back(new CircleEntity(width / 2.f, height / 2.f, height / 5.f));

		break;
	}
	case 2: {

		width = 4096.f;
		height = 2160.f;
		
		break;
		}
	default: break;
	}
}

Vector2 Map::getSpawnPoint(int player)
{
	float x, y;
	x = y = 50.f;
	switch (_mapGenID) {
	case 0: {
		switch (player) {
		case 1: {
			x = 100.f;
			y = 200.f;
			break;
		}
		case 2: {
			x = 400.f;
			y = 200.f;
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			break;
		}
		default:
			break;
		}
		break;
	}
	case 1:
	case 2: {
		switch (player) {
		case 1: {
			x = width / 4.f;
			y = height / 2.f;
			break;
		}
		case 2: {
			x = width / 4.f * 3.f;
			y = height / 2.f;
			break;
		}
		case 3: {
			x = width / 2.f;
			y = height / 4.f;
			break;
		}
		case 4: {
			x = width / 2.f;
			y = height / 4.f * 3.f;
			break;
		}
		default:
			break;
		}
		break;
	}
	}

	
	return Vector2{ x, y };
}

/**
Generates a point on the map which wont collide with any map entity, accorting to the width and height

@param width The width of the entity.
@param height The height of the entity.
@return a position with x and y of the spawn point
*/
Vector2 Map::getRandomSpawnPoint(float wdt, float hgt)
{
	float x, y;

	bool success = false;
	int tries = 0;
	while (!success) {
		x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / width));
		y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / height));
		success = true;
		for (int i = 0; i < _walls.size(); ++i) {
			Entity* wall{ _walls.at(i) };

			/*Check if the wall can collide with the point*/
			if (std::abs(wall->posX - x) < (wdt / 2 + wall->width / 2) || std::abs(wall->posY - y) < (hgt / 2 + wall->height / 2)) {
				success = false;
				break;
			}
		}
		if (tries >= 1000) {
			break;
		}
	}
	
	return Vector2{ x, y };
}

Vector2 Map::getRandomSpawnPointFrom(float px, float py, float maxDistance, float wdt, float hgt)
{
	float x, y;

	bool success = false;
	int tries = 0;
	while (!success) {
		x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (px - maxDistance/2 , px + maxDistance/2)));
		y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (py - maxDistance / 2 , py + maxDistance / 2)));
		success = true;
		for (int i = 0; i < _walls.size(); ++i) {
			Entity* wall{ _walls.at(i) };

			/*Check if the wall can collide with the point*/
			if (std::abs(wall->posX - x) < (wdt / 2 + wall->width / 2) || std::abs(wall->posY - y) < (hgt / 2 + wall->height / 2)) {
				success = false;
				break;
			}
		}
		++tries;
		if (tries >= 1000) {
			break;
		}
	}

	return Vector2{ x, y };

}
