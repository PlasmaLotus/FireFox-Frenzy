
#ifndef _PROJECTILE_FIRE_
#define _PROJECTILE_FIRE_

#include "AOEProjectile.h"
class ProjectileFire :
	public AOEProjectile
{
public:
	ProjectileFire();
	ProjectileFire(int id, float x, float y);
	ProjectileFire(int id);
	 ~ProjectileFire();

	void update(int32_t dt);
	bool isAlive();
	void handleCollision();
	void handleCollision(Entity *e);
	void _spawnNewAOE();
};

#endif //Projectile fire