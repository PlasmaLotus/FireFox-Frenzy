#include "Projectile.h"
#include "Player.h"
#include "../States/StateManager.h"
#include "GameLogic.h"

Projectile::Projectile(int pID) :
	Projectile(pID, 0.f, 0.f)
{
}
	

Projectile::Projectile(): 
	Projectile(getID(), 0.f, 0.f)
{
}

Projectile::Projectile(int pID, float x, float y) :
	CircleEntity(x, y, GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM),
	_playerID(pID),
	lifetime{ 6000 },
	durability{ 1 },
	orientationX{ 0.f },
	orientationY{ 0.f },
	power{ 1 }
{
}


Projectile::~Projectile(){
}

void Projectile::update(int32_t dt)
{
	CircleEntity::update(dt);
	prevPosX = posX;
	prevPosY = posY;
	posX += std::sin(orientation) * velocityX * dt;
	posY += std::cos(orientation) * velocityY * dt;
	lifetime-= dt;
	/*
	static float total_time = 0.00001;
	total_time += dt * 100;
	//p->velocityX = p->velocityX * sin(total_time);
	*/
}

bool Projectile::isAlive() {
	return (durability > 0 && lifetime > 0);
	//return (lifetime > 0);
}

bool Projectile::collidableWith(Entity* e){
	return true;
}

bool Projectile::collidableWith(Item* e) {
	return false;
} 
bool Projectile::collidableWith(Projectile* e){
	return (e->getPlayerID() != getPlayerID());
}

bool Projectile::collidableWith(Player* e){
	return (e->getID() != getPlayerID());
}

void Projectile::handleCollision()
{
	--durability;
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::CollisionGeneral, getID()));
}

void Projectile::handleCollisionMap()
{
	--durability;
	//StateManager::getInstance().eventManager.queueEvent(Event(EventType::CollisionGeneral, getID()));
}

void Projectile::handleCollision(Entity *e)
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

bool Projectile::testCollision(Entity * e)
{
	try {
		if (e != nullptr) {
			CircleEntity* ce = dynamic_cast<CircleEntity*>(e);
			SquareEntity* se = dynamic_cast<SquareEntity*>(e);
			Player* pe = dynamic_cast<Player*>(e);
			Projectile *pre = dynamic_cast<Projectile*>(e);
			Item *ie = dynamic_cast<Item*>(e);

			if (pe != nullptr) {
				return (collidableWith(pe) ? CircleEntity::testCollision(*pe) : false);
			}
			else if (pre != nullptr) {
				return (collidableWith(pre) ? CircleEntity::testCollision(*pre) : false);
			}
			else if (ie != nullptr) {
				return (collidableWith(ie) ? CircleEntity::testCollision(*ie) : false);
			}
			else if (ce != nullptr) {
				return CircleEntity::testCollision(*ce);
			}
			else if (se != nullptr) {
				return CircleEntity::testCollision(*se);
			}
			else {
				return (collidableWith(e) ? CircleEntity::testCollision(*e) : false);
			}
		}
		else
			return false;
	}
	catch (const std::bad_cast& cast) {
		return false;
	}
}

int Projectile::getPlayerID()
{
	return _playerID;
}