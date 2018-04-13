#include "Shield.h"
#include "Player.h"
#include "GameLogic.h"
Shield::Shield(Player * pID):
	Projectile(),
	playerPtr(pID){
	setRadius(GameLogic::PLAYER_SHIELD_RADIUS);
	if (playerPtr != nullptr) {
		_playerID = playerPtr->getID();
	}
}

Shield::Shield():
	Shield(nullptr){
}

Shield::~Shield(){
}

void Shield::update(int32_t dt){
	Projectile::update(dt);
	if (playerPtr != nullptr) {
		posX = playerPtr->posX;
		posY = playerPtr->posY;
	}
}

void Shield::handleCollision(){
	/*
	if (playerPtr != nullptr) {
		playerPtr->_loseAmmo(1);
		--durability;
	}
	*/
}

void Shield::handleCollision(Entity *e){
}


