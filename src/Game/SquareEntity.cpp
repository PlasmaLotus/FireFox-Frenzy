#include "SquareEntity.h"
#include "CircleEntity.h"
//#include "../States/StateManager.h"

SquareEntity::SquareEntity() :
MovingEntity()
//prevPosX(0.f),
//prevPosY(0.f),
//prevPosZ(0.f),
//velocityZ(0.f),
//velocityX(0.f),
//velocityY(0.f)
{
}

SquareEntity::~SquareEntity()
{
}

SquareEntity::SquareEntity(float pX, float pY, float wdth, float hght) {
	posX = pX;
	posY = pY;
	prevPosX = pX;
	prevPosY = pY;
	width = wdth;
	height = hght;
}

void SquareEntity::update(int dt)
{
}

void MovingEntity::update(int dt)
{
	prevPosX = posX;
	prevPosY = posY;
}

bool SquareEntity::testCollision(Entity e) {
	return false;
}
bool SquareEntity::testCollision(SquareEntity e) {
	return false;
}
bool SquareEntity::testCollision(CircleEntity e) {
	return false;
}

void SquareEntity::handleCollision()
{
}