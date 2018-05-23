#include "RapidFirePowerUp.h"
#include "../GameLogic.h"

#include "../../States/StateManager.h"


RapidFirePowerUp::RapidFirePowerUp(GameLogic* gc):
	PowerUp(gc)
{
	altSpawn = true;
	minimumChargeTime = GameLogic::PLAYER_RAPIDFIRE_PROJECTILE_MINIMUM_CHARGE_TIME;
	maximumChargeTime = GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME;
	lifetime = 5000;
}

RapidFirePowerUp::~RapidFirePowerUp() {
}

void RapidFirePowerUp::update(int dt){
	PowerUp::update(dt);

}

Projectile * RapidFirePowerUp::getProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new Projectile(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

void RapidFirePowerUp::spawnProjectile(int id, float x, float y, float orientation)
{
	if (altSpawn) {
		Projectile *p1{ new Projectile(id, x, y) };
		Projectile *p2{ new Projectile(id, x, y) };
		p1->velocityX = GameLogic::PROJECTILE_SPEED_MINIMUM;
		p1->velocityY = GameLogic::PROJECTILE_SPEED_MINIMUM;
		p1->setRadius(GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM);
		p1->power = 1;

		p2->velocityX = GameLogic::PROJECTILE_SPEED_MINIMUM;
		p2->velocityY = GameLogic::PROJECTILE_SPEED_MINIMUM;
		p2->setRadius(GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM);
		p2->power = 1;
		//p->lifetime = 700;
		p1->orientation = orientation - 0.1;
		p2->orientation = orientation + 0.1;
		_projectilesToSpawnThisTick--;
		_game->addEntity(p1);
		_game->addEntity(p2);
		//altSpawn = false;

	}
	else{
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

	}
	altSpawn = !altSpawn;
	_projectileSpawned = true;

	StateManager::getInstance().eventManager.queueEvent(Event(EventType::ProjectileSpawnRapid));

}

Projectile * RapidFirePowerUp::getProjectileAlt(int id, float x, float y, float orientation)
{
	return getProjectile(id,  x,  y,  orientation);
}

bool RapidFirePowerUp::isAlive(){
	return (lifetime >= 0);
}
