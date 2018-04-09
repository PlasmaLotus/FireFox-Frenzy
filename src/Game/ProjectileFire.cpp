#include "ProjectileFire.h"



ProjectileFire::ProjectileFire()
{
}


ProjectileFire::~ProjectileFire()
{
}

void ProjectileFire::update(int32_t dt)
{
	Projectile::update(dt);
}

bool ProjectileFire::isAlive()
{
	return false;
}

void ProjectileFire::handleCollision()
{
}

void ProjectileFire::handleCollision(Entity * e)
{
}
