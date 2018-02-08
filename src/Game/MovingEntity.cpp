#include "MovingEntity.h"
//#include "../States/StateManager.h"

MovingEntity::MovingEntity() :
Entity(),
prevPosX(0.f),
prevPosY(0.f),
prevPosZ(0.f),
velocityX(0.f),
velocityY(0.f),
velocityZ(0.f)
{
	//
}

MovingEntity::~MovingEntity()
{
}

void MovingEntity::update(int dt)
{
	/*
	prevPosX = posX;
	prevPosY = posY;
	prevPosZ = posZ;

	posX += velocityX;
	posY += velocityY;
	posZ += velocityZ;
	*/
}
