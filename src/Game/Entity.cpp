#include "Entity.h"
#include "../States/StateManager.h"
#include "GameLogic.h"
Entity::Entity() :
_id(StateManager::getInstance().getUniqueID()),
orientation(0.f),
_collisionDelay(GameLogic::PROJECTILE_COLLISION_DELAY_GENERAL),
_hitlagFrames(0),
_inHitlag(false){
}

Entity::~Entity()
{
	_collisions.clear();
}


void Entity::update(int32_t dt)
{
	for (int i = _collisions.size() - 1; i >= 0; i--) {
		CollisionStack stack = _collisions.at(i);
		stack.delay -= dt;
		if (stack.delay < 0) {
			_collisions.erase(_collisions.begin() + i);
		}
	}

	if (_hitlagFrames > 0) {
		_hitlagFrames -= dt;
	}
	else {
		_hitlagFrames = 0;
	}
	/**/
}

bool Entity::isAlive() {
	return true;
}

int Entity::getID() {
	return _id;
}

bool Entity::isID(int id) {
	return (id == _id);
}

bool Entity::collidableWith(Entity e)
{
	return true;
}

bool Entity::testCollision(Entity* e) {
	if (e != nullptr) {
		return (_testVerticalCollision(*e) && _testHorizontalCollision(*e));
	}
	else {
		return false;
	}
}

bool Entity::testCollision(Entity e) {
	return (_testVerticalCollision(e) && _testHorizontalCollision(e));
}

void Entity::handleCollision()
{
}

void Entity::handleCollision(Entity * e)
{
	handleCollision();
}

bool Entity::_testVerticalCollision(Entity e)
{
	float tp1 = posY - height / 2;
	float tp2 = posY + height / 2;

	float p1 = e.posY - e.height / 2;
	float p2 = e.posY + e.height / 2;


	return ((p1 >= tp1 && p1 <= tp2) || (p2 >= tp1 && p2 <= tp2));
	//return false;
}

bool Entity::_testHorizontalCollision(Entity e)
{

	float tp1 = posX - width / 2;
	float tp2 = posX + width / 2;

	float p1 = e.posX - e.width / 2;
	float p2 = e.posX + e.width / 2;


	return ((p1 >= tp1 && p1 <= tp2) || (p2 >= tp1 && p2 <= tp2));
	//return false;
}

float Entity::_distanceBetween(Entity e) {
	return _distanceBetween(e.posX, e.posY);
}
float Entity::_distanceBetween(Vector2 v) {
	return _distanceBetween(v.x, v.y);
}
float Entity::_distanceBetween(float x, float y) {
	return std::pow(std::pow(std::abs(posX - x),2) + std::pow(std::abs(posY - y),2), 0.5);
}