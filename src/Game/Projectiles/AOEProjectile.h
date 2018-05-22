#ifndef _AOE_PROJECTILE_
#define _AOE_PROJECTILE_


#include "../Projectile.h"
class AOEProjectile :
	public Projectile
{
public:
	AOEProjectile();
	AOEProjectile(int id, float x, float y);
	AOEProjectile(int id);
	virtual ~AOEProjectile();

	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	virtual bool testCollision(Entity*e);
	virtual void _spawnNewAOE();
	std::vector<Projectile> m_projectiles;
	int m_AOEProjectileSpawnTimer;
	int m_AOEProjectileSpawnCounter;
	bool m_mainProjectileActive;
};

#endif