#include "BubblePowerup.h"
#include "../GameLogic.h"
#include "../Projectiles\ProjectileBubble.h"


BubblePowerUp::BubblePowerUp(GameLogic* gc):
	PowerUp(gc)
{
	lifetime = 5000;
}

BubblePowerUp::~BubblePowerUp() {
}

void BubblePowerUp::update(int dt){
	PowerUp::update(dt);
	/*
	_projectilesToSpawnThisTick = 1;
	_projectileSpawned = false;
	*/
}

Projectile * BubblePowerUp::getProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new ProjectileBubble(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

Projectile * BubblePowerUp::spawnProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new ProjectileBubble(id, x, y) };
	//p->durability = 1;
	p->velocityX = GameLogic::PROJECTILE_SPEED_MINIMUM;
	p->velocityY = GameLogic::PROJECTILE_SPEED_MINIMUM;
	p->setRadius(GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM);
	p->power = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_game->addEntity(p);
	_projectileSpawned = true;
	return nullptr;
	//ga
}

Projectile * BubblePowerUp::getProjectileAlt(int id, float x, float y, float orientation)
{
	return getProjectile(id,  x,  y,  orientation);
}

bool BubblePowerUp::isAlive(){
	return (lifetime >= 0);
}
