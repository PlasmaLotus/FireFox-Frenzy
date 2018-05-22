#include "Enemy.h"
#include "../Player.h"
#include "../../States/StateManager.h"
#include "../GameLogic.h"

Enemy::Enemy() :
	Enemy(0.f, 0.f)
{
}

Enemy::Enemy(float x, float y) :
	Projectile(-1, x, y)
{
	power = 10;
	durability = 1;
	//orientationX = 0.f;
	//orientationY = 0.f;
}


Enemy::~Enemy(){
}

void Enemy::update(int32_t dt)
{
	Projectile::update(dt);
	prevPosX = posX;
	prevPosY = posY;
	posX += std::sin(orientation) * velocityX * dt;
	posY += std::cos(orientation) * velocityY * dt;
	//lifetime-= dt;

}

bool Enemy::isAlive() {
	return (durability > 0 );
}

/*
bool Enemy::collidableWith(Entity* e){
	return true;
}

bool Enemy::collidableWith(Item* e) {
	return false;
} 
bool Enemy::collidableWith(Projectile* e){
	return (e->getPlayerID() != getPlayerID());
}

bool Enemy::collidableWith(Player* e){
	return (e->getID() != getPlayerID());
}
*/
void Enemy::handleCollision()
{
	--durability;
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::CollisionGeneral, getID()));
}

void Enemy::handleCollisionMap()
{
	//--durability;
	//StateManager::getInstance().eventManager.queueEvent(Event(EventType::CollisionGeneral, getID()));
}

void Enemy::handleCollision(Entity *e)
{

	try {
		Player *p = dynamic_cast<Player *>(e);
		if (p != nullptr) {
			//handlecollisoin with player;
			handleCollision();
		}
	}
	catch (const std::bad_cast& cast) {
	}
	try {
		Projectile *p = dynamic_cast<Projectile *>(e);
		if (p != nullptr) {
			//handlecollisoin with Projectile;
			//handleCollision();
		}
	}
	catch (const std::bad_cast& cast) {
	}
	//else donothing
}

bool Enemy::testCollision(Entity * e)
{
	return CircleEntity::testCollision(e);
}
