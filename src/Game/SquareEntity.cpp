#include "SquareEntity.h"
#include "CircleEntity.h"
#include "GameLogic.h"

SquareEntity::SquareEntity() :
SquareEntity(0, 0, GameLogic::ENTITY_MINIMUM_WIDTH, GameLogic::ENTITY_MINIMUM_HEIGHT)
{
}

SquareEntity::~SquareEntity(){
}

SquareEntity::SquareEntity(float pX, float pY, float wdth, float hght):
Entity(){
	posX = pX;
	posY = pY;
	prevPosX = pX;
	prevPosY = pY;
	width = wdth;
	height = hght;
}

void SquareEntity::update(int32_t dt){
	Entity::update(dt);
}

/*Return false if no collision*/
bool SquareEntity::testCollision(Entity e) {
	return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}
bool SquareEntity::testCollision(SquareEntity e) {
	return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}
bool SquareEntity::testCollision(CircleEntity e) {
	Vector2 v1{ posX - width / 2, posY - height / 2 };
	Vector2 v2{ posX - width / 2, posY + height / 2 };
	Vector2 v3{ posX + width / 2, posY + height / 2 };
	Vector2 v4{ posX + width / 2, posY - height / 2 };
	return (e._distanceBetween(v1) <= e.width || e._distanceBetween(v2) <= e.width ||
		e._distanceBetween(v3) <= e.width || e._distanceBetween(v4) <= e.width);
}

void SquareEntity::handleCollision(){
}

void SquareEntity::handleCollision( Entity *e){
	handleCollision();
}

bool SquareEntity::testCollision(Entity * e)
{
	if (e != nullptr) {
		CircleEntity* ce = dynamic_cast<CircleEntity*>(e);
		SquareEntity* se = dynamic_cast<SquareEntity*>(e);
		if (ce != nullptr) {
			return testCollision(*ce);
		}
		else if (se != nullptr) {
			return testCollision(*se);
		}
		else {
			return testCollision(*e);
		}
	}
	else
		return false;
}

