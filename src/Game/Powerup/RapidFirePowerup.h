#ifndef __RapidFirePowerUp__
#define __RapidFirePowerUp__

#include "Powerup.h"
//enum PowerUpType { Normal, Fire, Ice, Plasma };
//class GameLogic;
class RapidFirePowerUp: public PowerUp {
public:
	RapidFirePowerUp(GameLogic* gc);
	~RapidFirePowerUp();

	void update(int dt);
	bool altSpawn;
	Projectile* getProjectile(int id, float x, float y, float orientation);
	void spawnProjectile(int id, float x, float y, float orientation);
	Projectile* getProjectileAlt(int id, float x, float y, float orientation);
	bool isAlive();
	//GameLogic* _game;
}; 
#endif //PowerUp 