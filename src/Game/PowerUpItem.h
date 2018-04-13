#ifndef __PowerUpItem__
#define __PowerUpItem__
#include "Item.h"
#include "PowerUp.h"

class PowerUpItem :
	public Item
{
public:
	PowerUpItem();
	PowerUpItem(float x, float y);
	virtual ~PowerUpItem();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	PowerUp powerUp;
};
#endif //PowerUpItem