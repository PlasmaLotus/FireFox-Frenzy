#include "Projectile.h"
#include "Player.h"
#include "../Event/EventManager.h"

Projectile::Projectile(Player* pID) :
	CircleEntity(0, 0, 10),
	playerPtr(pID),
	lifetime{ 3000 },
	durability{ 1 },
	orientationX{ 0.f },
	orientationY{ 0.f } 
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
	prevPosX = posX;
	prevPosY = posY;
	//prevPosZ = posZ;
	float speedX = 0.f;
	float speedY = 0.f;
	//posX += std::sin(orientation) * dt * velocityX;
	//posY += std::cos(orientation) * dt * velocityY;
	posX += std::sin(orientation) * velocityX;
	posY += std::cos(orientation) * velocityY;
	lifetime-= dt;
	Entity::update(dt);
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
	EventManager::queueEvent(Event(EventType::CollisionGeneral, getID()));
}

void Projectile::handleCollision(Projectile p)
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