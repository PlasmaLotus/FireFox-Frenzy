#include "PowerUpItem.h"
#include "GameLogic.h"
//#include "Player.h"

PowerUpItem::PowerUpItem() :
	PowerUpItem(0, 0) {
}

PowerUpItem::PowerUpItem(float x, float y) :
	Item(x, y, GameLogic::POWERUP_RADIUS) {
}

PowerUpItem::~PowerUpItem() {
}

void PowerUpItem::update(int32_t dt) {
	Item::update(dt);
}

bool PowerUpItem::isAlive() {
	return true;
}

void PowerUpItem::handleCollision() {
}

void PowerUpItem::handleCollision(Entity * e) {
}