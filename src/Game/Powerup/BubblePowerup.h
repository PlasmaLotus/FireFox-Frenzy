#ifndef __BubblePowerUp__
#define __BubblePowerUp__

#include "../Powerup.h"
#include "../Projectiles/ProjectileBubble.h"

class BubblePowerUp: public PowerUp {
public:
	BubblePowerUp(GameLogic* gc);
	virtual ~BubblePowerUp();

	virtual void update(int dt);
	virtual Projectile* getProjectile(int id, float x, float y, float orientation);
	virtual Projectile* spawnProjectile(int id, float x, float y, float orientation);
	virtual Projectile* getProjectileAlt(int id, float x, float y, float orientation);
	virtual bool isAlive();
	int spawnOffset;
}; 
#endif //PowerUp 