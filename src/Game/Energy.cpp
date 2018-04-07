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

Energy::Energy(Vector2 v, int amount) :
	Energy(v.x, v.y, amount)
{
}

Energy::Energy(float x, float y, int amount): 
Item(x, y, GameLogic::ENERGY_MINIMUM_RADIUS),
_collision(false),
aura(amount)
{
	state = ItemState::ItemCooldown;
	_stateCooldown = GameLogic::ENERGY_ITEM_COOLDOWN;
	//calc radius
	setRadius((GameLogic::ENERGY_MAX_RADIUS - GameLogic::ENERGY_MINIMUM_RADIUS) * amount / GameLogic::ENERGY_MAX_AURA + GameLogic::ENERGY_MINIMUM_RADIUS);
	lifetime = 10000;
	_alive = true;
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
		lifetime -= dt;
		if (lifetime < 0) {
			_alive = false;
		}
		break;
	}
	default:break;
	}

}

bool Energy::isAlive()
{
	return _alive;
}

void Energy::handleCollision()
{
	_collision = true;
	_alive = false;
}

void Energy::handleCollision(Entity * e)
{
	//handleCollision();
}
