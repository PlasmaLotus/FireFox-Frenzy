#ifndef __Item__
#define __Item__

#include "CircleEntity.h"
enum ItemState{ ItemSpawn, ItemCooldown, ItemActive };
class Item :
	public CircleEntity
{
public:
	Item();
	Item(float x, float y, float r);
	virtual ~Item();

	virtual void update(int32_t dt);
	virtual bool isAlive();
	virtual void handleCollision();
	virtual void handleCollision(Entity *e);
	
	ItemState state;
	//int _cooldownTimer;

};
#endif // !Item