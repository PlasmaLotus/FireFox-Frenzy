#include "CircleEntity.h"
#include "SquareEntity.h"
#include "GameLogic.h"

CircleEntity::CircleEntity() :
CircleEntity(0,0,GameLogic::ENTITY_MINIMUM_RADIUS){
}

CircleEntity::CircleEntity(float pX, float pY, float r) :
Entity(){
	posX = pX;
	posY = pY;
	prevPosX = pX;
	prevPosY = pY;
	setRadius(r);
}

CircleEntity::~CircleEntity(){
}

void CircleEntity::update(int32_t dt){
	Entity::update(dt);
}

bool CircleEntity::testCollision(Entity * e)
{
	if (e != nullptr) {
		CircleEntity* ce = dynamic_cast<CircleEntity*>(e);
		SquareEntity* se = dynamic_cast<SquareEntity*>(e);
		if (ce != nullptr) {
			return testCollision(*ce);
		}
		else if(se != nullptr){
			return testCollision(*se);
		}
		else {
			return testCollision (*e);
		}
	}
	else
		return false;
}

bool CircleEntity::testCollision(Entity e) {
	return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}
bool CircleEntity::testCollision(SquareEntity e) {
	Vector2 v1{ e.posX - e.width / 2, e.posY - e.height / 2 };
	Vector2 v2{ e.posX - e.width / 2, e.posY + e.height / 2 };
	Vector2 v3{ e.posX + e.width / 2, e.posY + e.height / 2 };
	Vector2 v4{ e.posX + e.width / 2, e.posY - e.height / 2 };
	return (_distanceBetween(v1) <= width || _distanceBetween(v2) <= width ||
		_distanceBetween(v3) <= width || _distanceBetween(v4) <= width);
}
bool CircleEntity::testCollision(CircleEntity e) {
	return (_distanceBetween(e.posX, e.posY) <= (width/2 + e.width/2));
}

void CircleEntity::handleCollision(){
}

void CircleEntity::handleCollision(Entity *e){
	handleCollision();
}

void CircleEntity::setRadius(float r){
	width = r;
	height = r;
}
