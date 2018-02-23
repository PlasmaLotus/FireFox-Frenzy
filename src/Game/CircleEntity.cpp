#include "CircleEntity.h"
#include "SquareEntity.h"
//#include "../States/StateManager.h"

CircleEntity::CircleEntity() :
MovingEntity()
//prevPosX(0.f),
//prevPosY(0.f),
//prevPosZ(0.f),
//velocityZ(0.f),
//velocityX(0.f),
//velocityY(0.f)
{
}

CircleEntity::CircleEntity(float pX, float pY, float r) {
	posX = pX;
	posY = pY;
	prevPosX = pX;
	prevPosY = pY;
	radius = r;
}

CircleEntity::~CircleEntity()
{
}

void CircleEntity::update(int dt)
{
}

bool CircleEntity::testCollision(Entity e) {
	return false;
}
bool CircleEntity::testCollision(SquareEntity e) {
	return false;
}
bool CircleEntity::testCollision(CircleEntity e) {
	return false;
}

void CircleEntity::handleCollision()
{
}
