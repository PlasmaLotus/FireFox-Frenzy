#include "Item.h"
#include "GameLogic.h"


Item::Item():
	Item(0.f, 0.f, GameLogic::ENTITY_MINIMUM_RADIUS){
}

Item::Item(float x, float y, float r):
CircleEntity(x, y, r),
state{ ItemState::ItemCooldown },
_stateCooldown(0) {

}
Item::~Item(){
}

void Item::update(int32_t dt){
}

bool Item::isAlive(){
	return true;
}

void Item::handleCollision(){
}

void Item::handleCollision(Entity * e){
}
