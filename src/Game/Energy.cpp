#include "Energy.h"
#include "GameLogic.h"

Energy::Energy():
	Energy(0.f, 0.f, 0)
{
}

Energy::Energy(int amount):
Energy(0.f, 0.f, amount)
{
}

Energy::Energy(float x, float y, int amount): 
Item(x, y, GameLogic::ENERGY_MINIMUM_RADIUS),
_collision(false)
{
	state = ItemState::ItemCooldown;
	_stateCooldown = GameLogic::ENERGY_ITEM_COOLDOWN;

	//calc radius
	
}

Energy::~Energy()
{
}

void Energy::update(int32_t dt)
{
	switch (state) {
	case ItemState::ItemCooldown: {
		_stateCooldown -= dt;
		if (_stateCooldown <= 0) {
			_stateCooldown = 0;
			state = ItemState::ItemActive;
		}
		break;
	}
	case ItemState::ItemActive: {
		break;
	}
	default:break;
	}

}

bool Energy::isAlive()
{
	return true;
}

void Energy::handleCollision()
{
	_collision = true;
}

void Energy::handleCollision(Entity * e)
{
	handleCollision();
}
