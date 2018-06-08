#include "BubblePowerup.h"
#include "../GameLogic.h"
#include "../Projectiles\ProjectileBubble.h"
#include "../../States/StateManager.h"

BubblePowerUp::BubblePowerUp(GameLogic* gc):
	PowerUp(gc)
{
	lifetime = 5000;
	minimumChargeTime = GameLogic::PLAYER_PROJECTILE_BUBBLE_MINIMUM_CHARGE_TIME;
	maximumChargeTime = GameLogic::PLAYER_PROJECTILE_BUBBLE_MAXIMUM_CHARGE_TIME;
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

Projectile * BubblePowerUp::getProjectile(int id, float x, float y, float orientation){
	Projectile *p{ new ProjectileBubble(id, x, y) };
	p->durability = 1;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_projectileSpawned = true;
	return p;
}

void BubblePowerUp::spawnProjectile(int id, float x, float y, float orientation)
{
	Projectile *p{ new ProjectileBubble(id, x, y) };
	//p->durability = 1;
	p->velocityX = GameLogic::PROJECTILE_BUBBLE_SPEED_MINIMUM;
	p->velocityY = GameLogic::PROJECTILE_BUBBLE_SPEED_MINIMUM;
	p->setRadius(GameLogic::PROJECTILE_BUBBLE_HITBOX_RADIUS_MINIMUM);
	p->power = 5;
	//p->lifetime = 700;
	p->orientation = orientation;
	_projectilesToSpawnThisTick--;
	_game->addEntity(p);
	_projectileSpawned = true;
	//StateMan
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::ProjectileSpawnBubble, p));

}

Projectile * BubblePowerUp::getProjectileAlt(int id, float x, float y, float orientation){
	return getProjectile(id,  x,  y,  orientation);
}

bool BubblePowerUp::isAlive(){
	return (lifetime >= 0);
}
