
#include "Item.h"

enum PowerUpType{Fire, Ice, Plasma};

class PowerUp :
	public Item
{
public:
	PowerUp();
	virtual ~PowerUp();
	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
};
