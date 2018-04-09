
#include "Projectile.h"
class ProjectileFire :
	public Projectile
{
public:
	ProjectileFire();
	virtual ~ProjectileFire();

	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	std::vector<Projectile*> m_projectiles;
};
