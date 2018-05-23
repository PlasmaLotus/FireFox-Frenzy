#include "ProjectileFire.h"
#include "../GameLogic.h"

ProjectileFire::ProjectileFire():
	AOEProjectile(-1, 0.f, 0.f){
}

ProjectileFire::ProjectileFire(int id) :
	AOEProjectile(id, 0.f, 0.f){
}

ProjectileFire::ProjectileFire(int id, float x, float y) :
	AOEProjectile(id, x, y)
{
	m_AOEProjectileSpawnTimer = 0;
	lifetime = 600;
	power = 10;
	m_AOEProjectileSpawnCounter = GameLogic::PROJECTILE_FIRE_AOE_SPAWN_INTERVAL;
	_spawnNewAOE();
}

ProjectileFire::~ProjectileFire()
{
}

void ProjectileFire::update(int32_t dt)
{
	AOEProjectile::update(dt);
	/*
	m_AOEProjectileSpawnTimer += dt;
	for (int i = m_projectiles.size() - 1; i >= 0; --i) {
		Projectile &p{ m_projectiles.at(i) };
		p.update(dt);
		if (!p.isAlive()) {
			m_projectiles.erase(m_projectiles.begin() + i);
		}
	}
	*/

}

bool ProjectileFire::isAlive(){
	//return true;
	return (m_projectiles.size() > 0 || lifetime > 0 || m_mainProjectileActive);
}

void ProjectileFire::handleCollision()
{
}

void ProjectileFire::handleCollision(Entity * e)
{
}

void ProjectileFire::_spawnNewAOE() {
	Projectile p(this->getPlayerID(), this->posX, this->posY);
	p.velocityX = 0.f;
	p.velocityY = 0.f;
	p.lifetime = 1500;
	p.power = 10;
	p.setRadius(width * 3);
	p._collisionDelay = 10;
	m_projectiles.push_back(p);
}