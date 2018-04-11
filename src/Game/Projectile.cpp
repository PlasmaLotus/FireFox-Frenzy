#include "Projectile.h"
#include "Player.h"
#include "../States/StateManager.h"

Projectile::Projectile(Player* pID) :
	CircleEntity(0, 0, 10),
	playerPtr(pID),
	lifetime{ 3000 },
	durability{ 1 },
	orientationX{ 0.f },
	orientationY{ 0.f },
	power{1}
{
}
	

Projectile::Projectile(): 
	Projectile(nullptr)
{

}

Projectile::~Projectile(){
}

void Projectile::update(int32_t dt)
{
	CircleEntity::update(dt);
	prevPosX = posX;
	prevPosY = posY;
	//posX += std::sin(orientation) * dt * velocityX;
	//posY += std::cos(orientation) * dt * velocityY;
	posX += std::sin(orientation) * velocityX;
	posY += std::cos(orientation) * velocityY;
	lifetime-= dt;
}

bool Projectile::isAlive() {
	//return (durability > 0 && lifetime > 0);
	return (lifetime > 0);
}

bool Projectile::collidableWith(Entity e)
{
	return true;
}

bool Projectile::collidableWith(Projectile e)
{
	return (e.getPlayerID() != getPlayerID());
}

bool Projectile::collidableWith(Player e)
{
	return (e.getID() != getPlayerID());
}

void Projectile::handleCollision()
{
	--durability;
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::CollisionGeneral, getID()));
}

void Projectile::handleCollision(Entity *e)
{
	handleCollision();
}

Player * Projectile::getPlayer()
{
	return playerPtr;
}

int Projectile::getPlayerID()
{
	return playerPtr->getID();
}