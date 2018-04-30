#include "SquareEntity.h"
#include "CircleEntity.h"
#include "GameLogic.h"
#include "Map.h"

Map::Map() :
	Map(GameLogic::MAP_DEFAULT_WIDTH, GameLogic::MAP_DEFAULT_HEIGHT)
{
}

Map::~Map(){
	for (int i = _walls.size() - 1; i >= 0; --i) {
		Entity* wall{ _walls.at(i) };
		if (wall != nullptr) {
			delete wall;
		}
	}
	_walls.clear();
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
			Entity* w{ _walls.at(i) };
			if (w->testCollision(e)) {
				collision = true;
				/*Collision with wall*/
				/*
				///Great integration, however, the object colliding with the wall is much smaller
				///Colliding in the middle of it results in a warp in the opposite axis as the direction colliding from
				float insertX = 0.f;
				float insertY = 0.f;

				if (e->posX >= w.posX) {
					//From the Right
					insertX = (e->width / 2 + w.width / 2) - (e->posX - w.posX);
				}
				else {
					//From the LEFT
					insertX = ( w.posX - e->posX) - (e->width / 2 + w.width / 2);
				}

				if (e->posY >= w.posY) {
					//From the Bottom
					insertY = (e->height / 2 + w.height / 2) - (e->posY - w.posY);
				}
				else {
					//From the TOP
					insertY = (w.posY - e->posY) - (e->height / 2 + w.height / 2);
				}

				if (std::abs(insertX) > std::abs(insertY)) {
					//X is higher
					e->posX += insertX;
				}
				else if (std::abs(insertX) < std::abs(insertY)) {
					//X is higher
					e->posY += insertY;
				}
				else {
					e->posX += insertX;
					e->posY += insertY;
				}
				*/
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
		width = 4096;
		height = 2160;
		_walls.push_back(new SquareEntity(700, 700, 100, 100));
		_walls.push_back(new CircleEntity(900, 900, 100));
		break;
		}
	default: break;
	}
}