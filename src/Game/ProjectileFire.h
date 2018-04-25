
#include "Projectile.h"
class ProjectileFire :
	public Projectile
{
public:
	ProjectileFire();
	ProjectileFire(int id, float x, float y);
	ProjectileFire(int id);
	virtual ~ProjectileFire();

	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	void _spawnNewAOE();
	std::vector<Projectile*> m_projectiles;
	int m_AOEProjectileSpawnTimer;
	int m_AOEProjectileSpawnCounter;
};
