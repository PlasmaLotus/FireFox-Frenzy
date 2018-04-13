#include "Item.h"
#include "GameLogic.h"

Item::Item():
	Item(0.f, 0.f, GameLogic::ENTITY_MINIMUM_RADIUS){
}

Item::Item(float x, float y, float r):
CircleEntity(x, y, r),
state{ ItemState::ItemCooldown },
_stateCooldown{ GameLogic::ENERGY_ITEM_COOLDOWN },
lifetime{ GameLogic::ITEM_MINIMUM_LIFETIME },
_alive{ true } {
}

Item::~Item(){
}

void Item::update(int32_t dt){
	CircleEntity::update(dt);
	switch (state) {
	case ItemState::ItemSpawn:
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

bool Item::isAlive(){
	return _alive;
}

void Item::handleCollision(){
}

void Item::handleCollision(Entity * e){
}
