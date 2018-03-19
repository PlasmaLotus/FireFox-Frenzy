#include "SquareEntity.h"
#include "CircleEntity.h"
//#include "../States/StateManager.h"

SquareEntity::SquareEntity() :
Entity()
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

void SquareEntity::update(int32_t dt)
{
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
	return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}

void SquareEntity::handleCollision()
{
}

void SquareEntity::handleCollision( Entity e)
{
	handleCollision();
}

