#include "Shield.h"
#include "Player.h"

Shield::Shield(Player * pID)
{
}

Shield::Shield()
{
}

Shield::~Shield()
{
}

void Shield::update(int32_t dt)
{
	Projectile::update(dt);
}

void Shield::handleCollision()
{
	if (playerPtr != nullptr) {
		playerPtr->_loseAmmo(1);
		--durability;
	}
}

void Shield::handleCollision(Projectile p)
{
}


