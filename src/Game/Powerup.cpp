#include "Powerup.h"



PowerUp::PowerUp()
{
}


PowerUp::~PowerUp()
{
}

void PowerUp::update(int32_t dt)
{
	Item::update(dt);
}

bool PowerUp::isAlive()
{
	return true;
}

void PowerUp::handleCollision()
{
}

void PowerUp::handleCollision(Entity * e)
{
}
