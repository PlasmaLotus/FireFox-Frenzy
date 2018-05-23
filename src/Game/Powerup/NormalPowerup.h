#ifndef __NormalPowerUp__
#define __NormalPowerUp__

#include "Powerup.h"
//enum PowerUpType { Normal, Fire, Ice, Plasma };
//class GameLogic;
class NormalPowerUp: public PowerUp {
public:
	NormalPowerUp(GameLogic* gc);
	~NormalPowerUp();

	void update(int dt);
	//int lifetime;
	Projectile* getProjectile(int id, float x, float y, float orientation);
	void spawnProjectile(int id, float x, float y, float orientation);
	Projectile* getProjectileAlt(int id, float x, float y, float orientation);
	bool isAlive();
	//GameLogic* _game;
}; 
#endif //PowerUp 