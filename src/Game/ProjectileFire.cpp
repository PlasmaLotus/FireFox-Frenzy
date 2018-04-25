#include "ProjectileFire.h"

ProjectileFire::ProjectileFire():
	Projectile(-1, 0.f, 0.f){
}

ProjectileFire::ProjectileFire(int id) :
	Projectile(id, 0.f, 0.f){
}

ProjectileFire::ProjectileFire(int id, float x, float y) :
	Projectile(id, x, y)
{
	_spawnNewAOE();
	m_AOEProjectileSpawnTimer = 0;
}

ProjectileFire::~ProjectileFire()
{
}

void ProjectileFire::update(int32_t dt)
{
	Projectile::update(dt);
	m_AOEProjectileSpawnTimer += dt;
	for (int i = m_projectiles.size() - 1; i >= 0; --i) {
		Projectile &p{ m_projectiles.at(i) };
		p.update(dt);
		if (!p.isAlive()) {
			m_projectiles.erase(m_projectiles.begin() + i);
		}
	}


}

bool ProjectileFire::isAlive(){
	return true;
}

void ProjectileFire::handleCollision()
{
}

void ProjectileFire::handleCollision(Entity * e)
{
}

void ProjectileFire::_spawnNewAOE() {

}