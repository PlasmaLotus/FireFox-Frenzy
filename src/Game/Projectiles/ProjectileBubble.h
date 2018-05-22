
#ifndef _PROJECTILE_BUBBLE_
#define _PROJECTILE_BUBBLE_

#include "../Projectile.h"
class ProjectileBubble :
	public Projectile
{
public:
	ProjectileBubble();
	ProjectileBubble(int id, float x, float y);
	ProjectileBubble(int id);
	virtual ~ProjectileBubble();

	virtual void update(int32_t dt);
	virtual bool isAlive();
	void handleCollision();
	void handleCollision(Entity *e);
};

#endif