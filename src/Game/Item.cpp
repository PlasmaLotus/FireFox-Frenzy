#include "Item.h"
#include "GameLogic.h"


Item::Item():
	Item(0.f, 0.f, GameLogic::ENTITY_MINIMUM_RADIUS){
}

Item::Item(float x, float y, float r):
CircleEntity(x, y, r),
state{ ItemCooldown },
_cooldownTimer{GameLogic::ITEM_MINIMUM_COOLDOWN_TIME} {
}

Item::~Item(){
}

void Item::update(int32_t dt){
	switch (state) {
	case ItemState::ItemCooldown: {
		_cooldownTimer -= dt;
		if (_cooldownTimer >= 0) {
			_cooldownTimer = 0;
			state = ItemState::ItemActive;
		}
		break;
	}
	case ItemState::ItemActive: {
		update(dt);
	}
	}
}

void Item::update(int dt) {

}

bool Item::isAlive(){
	return true;
}

void Item::handleCollision(){
}

void Item::handleCollision(Entity * e){
}
