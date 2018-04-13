#include "Powerup.h"
#include "GameLogic.h"


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
}

Projectile * PowerUp::getProjectile(int id, float x, float y)
{
	Projectile *p{ new Projectile(id, x, y) };
	p->durability = 1;
	p->lifetime = 600;
	return p;
}

bool PowerUp::isAlive(){
	return (lifetime >= 0);
}
