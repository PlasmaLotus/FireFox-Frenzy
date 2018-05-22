#include "PowerUpItem.h"
#include "GameLogic.h"
//#include "Player.h"

PowerUpItem::PowerUpItem(GameLogic * gc, PowerUp* p) :
	PowerUpItem(gc, p, 0, 0) {
}

PowerUpItem::PowerUpItem(GameLogic * gc, PowerUp* p, float x, float y) :
	Item(x, y, GameLogic::POWERUP_RADIUS),
	powerUp(p){
	lifetime = GameLogic::GAME_POWERUP_LIFETIME;
}

PowerUpItem::~PowerUpItem() {
}

void PowerUpItem::update(int32_t dt) {
	Item::update(dt);
}

bool PowerUpItem::isAlive() {
	return Item::isAlive();
}

void PowerUpItem::handleCollision() {
	Item::handleCollision();
}

void PowerUpItem::handleCollision(Entity * e) {
	Item::handleCollision(e);
}