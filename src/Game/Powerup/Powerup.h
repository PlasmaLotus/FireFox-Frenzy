#ifndef __PowerUp__
#define __PowerUp__

#include "../Projectile.h"
//enum PowerUpType { Normal, Fire, Ice, Plasma };
class GameLogic;
class PowerUp {
public:
	PowerUp(GameLogic* gc);
	virtual ~PowerUp();
	
	//PowerUpType powerUpType;
	virtual int onDamageTaken(int damage);
	virtual void onDash();
	virtual int onShieldDamageTaken(int damage);
	virtual void update(int dt);
	int lifetime;
	virtual Projectile* getProjectile(int id, float x, float y, float orientation);
	virtual void spawnProjectile(int id, float x, float y, float orientation);
	virtual Projectile* getProjectileAlt(int id, float x, float y, float orientation);
	int _projectilesToSpawnThisTick{ 1 };
	bool _projectileSpawned{ false };
	virtual bool isAlive();
	GameLogic* _game;
	int minimumChargeTime;
	int maximumChargeTime;
}; 
#endif //PowerUp 