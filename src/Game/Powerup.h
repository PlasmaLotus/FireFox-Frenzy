#ifndef __PowerUp__
#define __PowerUp__

#include "Projectile.h"
enum PowerUpType { Normal, Fire, Ice, Plasma };

class PowerUp {
public:
	PowerUp();
	virtual ~PowerUp();
	
	PowerUpType powerUpType;
	int onDamageTaken(int damage);
	void onDash();
	int onShieldDamageTaken(int damage);
	void update(int dt);
	int lifetime;
	virtual Projectile* getProjectile(int id, float x, float y, float orientation);
	virtual Projectile* spawnProjectile(int id, float x, float y, float orientation);
	virtual Projectile* getProjectileAlt(int id, float x, float y, float orientation);
	int _projectilesToSpawnThisTick{ 1 };
	bool _projectileSpawned{ false };
	bool isAlive();
}; 
#endif //PowerUp 