#ifndef __PowerUpItem__
#define __PowerUpItem__
#include "Item.h"
#include "Powerup/PowerUp.h"

class GameLogic;
class PowerUpItem :
	public Item
{
public:
	//PowerUpItem(GameLogic * gc);
	PowerUpItem(GameLogic * gc, PowerUp* p,float x, float y);
	PowerUpItem(GameLogic * gc, PowerUp* p);
	virtual ~PowerUpItem();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	PowerUp* powerUp;
};
#endif //PowerUpItem