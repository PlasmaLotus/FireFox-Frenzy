#include "Powerup.h"
#include "GameLogic.h"
#include "Projectiles\ProjectileBubble.h"


PowerUp::PowerUp():
lifetime(100){
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
}

Projectile * PowerUp::getProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new ProjectileBubble(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

Projectile * PowerUp::spawnProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new ProjectileBubble(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

Projectile * PowerUp::getProjectileAlt(int id, float x, float y, float orientation)
{
	return getProjectile(id,  x,  y,  orientation);
}

bool PowerUp::isAlive(){
	return (lifetime >= 0);
}
