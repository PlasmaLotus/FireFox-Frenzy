#include "AOEProjectile.h"

AOEProjectile::AOEProjectile():
	Projectile(-1, 0.f, 0.f){
}

AOEProjectile::AOEProjectile(int id) :
	Projectile(id, 0.f, 0.f){
}

AOEProjectile::AOEProjectile(int id, float x, float y) :
	Projectile(id, x, y),
	m_mainProjectileActive(true),
	m_AOEProjectileSpawnTimer(0),
	m_AOEProjectileSpawnCounter(1000)
{
	//_spawnNewAOE();
	//m_AOEProjectileSpawnTimer = 0;

}

AOEProjectile::~AOEProjectile()
{
	m_projectiles.clear();
}

void AOEProjectile::update(int32_t dt)
{
	Projectile::update(dt);
	m_AOEProjectileSpawnTimer += dt;
	if (m_AOEProjectileSpawnTimer >= m_AOEProjectileSpawnCounter) {
		m_AOEProjectileSpawnTimer -= m_AOEProjectileSpawnCounter;
		_spawnNewAOE();
	}

	for (int i = m_projectiles.size() - 1; i >= 0; --i) {
		Projectile &p{ m_projectiles.at(i) };
		p.update(dt);
		if (!p.isAlive()) {
			m_projectiles.erase(m_projectiles.begin() + i);
		}
	}

}

bool AOEProjectile::isAlive(){
	return true;
	//return (m_projectiles.size() > 0 || durability > 0 || lifetime > 0);
}

void AOEProjectile::handleCollision()
{
}

void AOEProjectile::handleCollision(Entity * e)
{
	//if()
}

bool AOEProjectile::testCollision(Entity * e)
{
	if (m_mainProjectileActive && e->testCollision(dynamic_cast<Projectile *>(this))) {
		return true;
	}
	else {
		for (int i = m_projectiles.size() - 1; i >= 0; --i) {
			Projectile &p{ m_projectiles.at(i) };
			if (p.testCollision(e) ){
				return true;
			}
		}
	}
	return false;
}

void AOEProjectile::_spawnNewAOE() {

}