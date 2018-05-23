#include "FirePowerup.h"
#include "../GameLogic.h"
#include "../Projectiles\ProjectileFire.h"


FirePowerUp::FirePowerUp(GameLogic* gc):
	PowerUp(gc)
{
	lifetime = 5000;
	minimumChargeTime = GameLogic::PLAYER_PROJECTILE_BUBBLE_MINIMUM_CHARGE_TIME;
	maximumChargeTime = GameLogic::PLAYER_PROJECTILE_BUBBLE_MAXIMUM_CHARGE_TIME;
}

FirePowerUp::~FirePowerUp() {
}

void FirePowerUp::update(int dt){
	PowerUp::update(dt);
	/*
	_projectilesToSpawnThisTick = 1;
	_projectileSpawned = false;
	*/
}

Projectile * FirePowerUp::getProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new ProjectileFire(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

void FirePowerUp::spawnProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new ProjectileFire(id, x, y) };
	//p->durability = 1;
	p->velocityX = GameLogic::PROJECTILE_BUBBLE_SPEED_MINIMUM;
	p->velocityY = GameLogic::PROJECTILE_BUBBLE_SPEED_MINIMUM;
	p->setRadius(GameLogic::PROJECTILE_BUBBLE_HITBOX_RADIUS_MINIMUM);
	p->power = 3;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_game->addEntity(p);
	_projectileSpawned = true;
	//return nullptr;
	//ga
}

Projectile * FirePowerUp::getProjectileAlt(int id, float x, float y, float orientation)
{
	return getProjectile(id,  x,  y,  orientation);
}

bool FirePowerUp::isAlive(){
	return (lifetime >= 0);
}
