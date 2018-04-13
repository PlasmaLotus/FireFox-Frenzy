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
	virtual Projectile* getProjectile(int id, float x, float y);
	bool isAlive();
}; 
#endif //PowerUp 