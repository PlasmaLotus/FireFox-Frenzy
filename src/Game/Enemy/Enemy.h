
#ifndef __Enemy__
#define __Enemy__
#include "../Projectile.h"

class Player;
//enum PlayerState { ShootWindup, Shooting, ShootCooldown, Moving };
class Enemy : public Projectile {
public:
	
	//int HP;
	//int power;
	Enemy();
	Enemy(float x, float y);
	virtual ~Enemy();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollisionMap();
	virtual void handleCollision(Entity *e);
	virtual bool testCollision(Entity * e);
protected:

};
#endif // !__PROJECTILE__