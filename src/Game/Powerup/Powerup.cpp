#include "Powerup.h"
#include "../GameLogic.h"
//#include "../Projectiles\ProjectileBubble.h"


PowerUp::PowerUp(GameLogic* gc):
lifetime(100000),
minimumChargeTime(GameLogic::PLAYER_PROJECTILE_MINIMUM_CHARGE_TIME),
maximumChargeTime(GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME),
_game(gc){
}

PowerUp::~PowerUp() {
}

int PowerUp::onDamageTaken(int damage){
	return damage;
}

void PowerUp::onDash()
{
}

int PowerUp::onShieldDamageTaken(int damage)
{
	return damage;
}

void PowerUp::update(int dt){
	_projectilesToSpawnThisTick = 1;
	_projectileSpawned = false;
	lifetime -= dt;
}

Projectile * PowerUp::getProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new Projectile(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

void PowerUp::spawnProjectile(int id, float x, float y, float orientation)
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

Projectile * PowerUp::getProjectileAlt(int id, float x, float y, float orientation)
{
	return getProjectile(id,  x,  y,  orientation);
}

bool PowerUp::isAlive(){
	return true;
}
