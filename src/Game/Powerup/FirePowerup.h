#ifndef __FirePowerUp__
#define __FirePowerUp__

#include "Powerup.h"
#include "../Projectiles/ProjectileFire.h"

class FirePowerUp: public PowerUp {
public:
	FirePowerUp(GameLogic* gc);
	virtual ~FirePowerUp();

	virtual void update(int dt);
	virtual Projectile* getProjectile(int id, float x, float y, float orientation);
	virtual void spawnProjectile(int id, float x, float y, float orientation);
	virtual Projectile* getProjectileAlt(int id, float x, float y, float orientation);
	virtual bool isAlive();
	int spawnOffset;
}; 
#endif //BubblePowerUp 