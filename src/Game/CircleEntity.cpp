#include "CircleEntity.h"
#include "SquareEntity.h"
//#include "../States/StateManager.h"

CircleEntity::CircleEntity() :
CircleEntity(0,0,0)
//prevPosX(0.f),
//prevPosY(0.f),
//prevPosZ(0.f),
//velocityZ(0.f),
//velocityX(0.f),
//velocityY(0.f)
{

}

CircleEntity::CircleEntity(float pX, float pY, float r) :
Entity()
{
	posX = pX;
	posY = pY;
	prevPosX = pX;
	prevPosY = pY;
	//radius = r;
	width = r;
	height = r;
}

CircleEntity::~CircleEntity()
{
}

void CircleEntity::update(int32_t dt)
{
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
	//return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}
bool CircleEntity::testCollision(CircleEntity e) {
	return (_distanceBetween(e.posX, e.posY) <= (width/2 + e.width/2));
	//return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}

void CircleEntity::handleCollision()
{
}

void CircleEntity::handleCollision(Entity *e)
{
	handleCollision();
}

void CircleEntity::setRadius(float r)
{
	width = r;
	height = r;
}
