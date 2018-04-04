
#include "Item.h"
class Energy :
	public Item
{
public:
	Energy();
	Energy(int amount);
	Energy(float x, float y, int amount);
	~Energy();

	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);


	int aura;
	bool _collision;
};
