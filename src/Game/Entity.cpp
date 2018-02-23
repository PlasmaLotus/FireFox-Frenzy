#include "Entity.h"
#include "../States/StateManager.h"

Entity::Entity() :
_id(StateManager::getInstance().getUniqueID()),

orientation(0.f){
	/*
	posX(0.f),
		posY(0.f),
		posZ(0.f),
	*/
}

Entity::~Entity()
{
}

void Entity::update(int dt)
{
}



