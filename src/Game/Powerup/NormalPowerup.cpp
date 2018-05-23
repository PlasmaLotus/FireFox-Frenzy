#include "NormalPowerup.h"
#include "../GameLogic.h"
//#include "../Projectiles\ProjectileBubble.h"


NormalPowerUp::NormalPowerUp(GameLogic* gc):
	PowerUp(gc)
{
	//_game = gc;
	minimumChargeTime = GameLogic::PLAYER_PROJECTILE_MINIMUM_CHARGE_TIME;
	maximumChargeTime = GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
	lifetime = 100000;
}

NormalPowerUp::~NormalPowerUp() {
}

void NormalPowerUp::update(int dt){
	PowerUp::update(dt);
	if (lifetime <= 0) {
		lifetime = 100000;
	}
}

Projectile * NormalPowerUp::getProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new Projectile(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

void NormalPowerUp::spawnProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new Projectile(id, x, y) };
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
	//return nullptr;
	//ga
}

Projectile * NormalPowerUp::getProjectileAlt(int id, float x, float y, float orientation)
{
	return getProjectile(id,  x,  y,  orientation);
}

bool NormalPowerUp::isAlive(){
	return true;
}
