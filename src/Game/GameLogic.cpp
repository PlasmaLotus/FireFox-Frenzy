/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameLogic.h"
#include "../Main.h"
#include "../States/StateManager.h"

const float GameLogic::PLAYER_MAX_VELOCITY(9.0f);
const float GameLogic::PLAYER_MAX_VELOCITY_DECREASE_RATE(0.06f);
const float GameLogic::PLAYER_MAX_VELOCITY_CAP_DECREASE_RATE(0.15f);
const float GameLogic::PLAYER_FRICTION(0.98f);
const float GameLogic::PLAYER_VELOCITY_DEAD_ZONE(0.001f);
const float GameLogic::PLAYER_ACCELERATION_RATE(0.06f);
const float GameLogic::PLAYER_DASH_VELOCITY(13.54f);
const float GameLogic::PLAYER_MINIMUM_DASH_VELOCITY(3.0f);
const float GameLogic::PLAYER_SHIELD_RADIUS(15.0f);

const float GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM( 5.f );
const float GameLogic::PROJECTILE_HITBOX_RADIUS_MAXIMUM( 20.f );
const float GameLogic::PROJECTILE_SPEED_MINIMUM( 3.0f );
const float GameLogic::PROJECTILE_SPEED_MAXIMUM( 9.0f );
const float GameLogic::ENTITY_MINIMUM_RADIUS{ 3.0f };
const float GameLogic::ENTITY_MINIMUM_WIDTH{ 3.0f };
const float GameLogic::ENTITY_MINIMUM_HEIGHT{ 3.0f };

const float GameLogic::ENERGY_MAX_RADIUS{ 20.f };
const float GameLogic::ENERGY_MINIMUM_RADIUS{ 5.f };

//const float GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME(2500);

GameLogic::GameLogic() :
	gameState(GameCurrentState::COUNTDOWN){
	init();
}

GameLogic::~GameLogic(){
	_playerIDs.clear();
	_emptyAllEntities();
	_entities.clear();
	_spawnPoints.clear();
}

void GameLogic::init() {
	_spawnPoints.clear();
	_spawnTimer = 0;
	for (int i = 4; i-- >= 0; ) {
		switch (i) {
		case 3: {
			_spawnPoints.push_back(Vector2{ 500.f, 500.f });
			break;
		}
		case 2: {
			_spawnPoints.push_back(Vector2{ 200.f, 500.f });
			break;
		}
		case 1: {
			_spawnPoints.push_back(Vector2{ 500.f, 200.f });
			break;
		}
		case 0: {
			_spawnPoints.push_back(Vector2{ 200.f, 200.f });
			break;
		}
		default:
			break;
		}
	}

	{
		Vector2 v1 = _spawnPoints.at(0);
		Vector2 v2 = _spawnPoints.at(1);
		Vector2 v3 = _spawnPoints.at(2);
		Vector2 v4 = _spawnPoints.at(3);
		Player *p1{ new Player(this, v1)};
		Player *p2{ new Player(this, v2) };
		Player *p3{ new Player(this, v3) };
		Player *p4{ new Player(this, v4) };
		/*
		p1->posX = v1.x;
		p1->posY = v1.y;
		p2->posX = v2.x;
		p2->posY = v2.y;
		p3->posX = v3.x;
		p3->posY = v3.y;
		p4->posX = v4.x;
		p4->posY = v4.y;
		*/

		_playerIDs.push_back(p1->getID());
		__playerIDs[0] = p1->getID();
		_playerIDs.push_back(p2->getID());
		__playerIDs[1] = p2->getID();
		_playerIDs.push_back(p3->getID());
		__playerIDs[2] = p3->getID();
		_playerIDs.push_back(p4->getID());
		__playerIDs[3] = p4->getID();

		_entities.push_back(p1);
		_entities.push_back(p2);
		//_entities.push_back(p3);
		//_entities.push_back(p4);
	}
	frame = 0;
	StateManager::getInstance().eventManager.queueEvent(Event(EventType::Countdown3));
}
void GameLogic::reset() {
	_emptyAllEntities();
	_entities.clear();
	init();
}

void GameLogic::tick() {
	dt = StateManager::getInstance().getElapsedTime();

	switch (gameState)
	{
	case::GameCurrentState::COUNTDOWN:
		countdownTimer -= dt;
		int it;
		if (countdownTimer > GAME_COUNTDOWN_TIME / 3 * 2) {
			it = 2;
		}
		if (countdownTimer > GAME_COUNTDOWN_TIME / 3) {
			it = 1;
		}
		if (it != _countdownIt) {
			if (it == 2) {
				StateManager::getInstance().eventManager.queueEvent(Event(EventType::Countdown2));
			}
			if (it == 1) {
				StateManager::getInstance().eventManager.queueEvent(Event(EventType::Countdown1));
			}
		}
		_countdownIt = it;

		if (countdownTimer <= 0){
			gameState = GameCurrentState::RUNNING;
			countdownTimer = 0;
			StateManager::getInstance().eventManager.queueEvent(Event(EventType::CountdownStart));
		}
		break;
	case GameCurrentState::RUNNING:
		//dt = StateManager::getInstance().getElapsedTime();
		//printf("GameTick:  DT - %ld\n", dt);
		frame++;
		_totalDT += dt;
		_spawnTimer += dt;
		if (_spawnTimer >= GAME_ENERGY_SPAWN_TIMER) {
			_spawnTimer -= GAME_ENERGY_SPAWN_TIMER;
			_spawnEnergy();
		}
		printf("MaxVelocity:%3.5f - Game Frame: %d\n", PLAYER_MAX_VELOCITY, frame);
		_handleEntitiesUpdate(dt);
		_handleEntitiesCollisions(dt);
		_handleEntitesEnd();
		_handleGameEnd();
		break;
	default:
		break;
	}
	
}

void GameLogic::pause() {
}

void GameLogic::_handleEntitiesUpdate(int32_t dt){
	printf("Volume of Entities: %d,\n", _entities.size());
	for (int i = _entities.size() - 1; i >= 0; i--) {
		Entity *e = _entities.at(i);
		e->update(dt);

		//Player Cast
		for (int pOffset = 0; pOffset < _playerIDs.size(); pOffset++) {
			if (e->getID() == _playerIDs.at(pOffset)) {
				try{
					Player *p = dynamic_cast<Player *>(e);
					printf("Player id-%d - HP:%d -  x:%3.2f - y:%3.2f | Ammo: %d/%d, %d/%d,\n", p->getID(), p->HP, p->posX, p->posY, p->ammo, PLAYER_MAX_AMMO, p->_ammoRechargeProgress, PLAYER_AMMO_RECHARGE_COOLDOWN);
					printf(" -- OriX:%3.2f - OriY:%3.2f | velocityX:%3.2f, velocityY:%3.2f\n", p->orientationX, p->orientationY, p->velocityX, p->velocityY);
				}
				catch (const std::bad_cast& cast){
				}
			}
		}
		
		if (!e->isAlive()) {
			addEntityIDToDelete(e->getID());
		}
	}
}

void GameLogic::_handleEntitiesCollisions(int32_t dt){
	for (int i = _entities.size() - 1; i >= 0; i--) {
		Entity *e1 = _entities.at(i);
		for (int j = _entities.size() - 1; j >= 0; j--) {
			Entity *e2 = _entities.at(j);
			if (e1 != e2) {
				if (e1->testCollision(*e2)) {
					e1->handleCollision(e2);
					//printf("Collision Detected, ID:%d, ID:%d -  Distance: %3.3f!!!\n", e1->getID(), e2->getID(), e1->_distanceBetween(*e2));
				}
			}
		}
	}
}

void GameLogic::_handleEntitesEnd(){
	int id;
	while (!_idsToDestroy.empty()) {
		id = _idsToDestroy.top();
		
		for (int i = _entities.size() - 1; i >= 0; i--) {
			if (_entities.at(i)->getID() == id) {
				delete _entities.at(i);
				_entities.erase(_entities.begin() + i);
			}
		}
		_idsToDestroy.pop();
	}
}

void GameLogic::_handleGameEnd() {
	int pAlive = 0;
	for (int i = _playerIDs.size() - 1; i >= 0; i--) {
		for (int j = 0; j < _entities.size(); j++) {
			Entity *e = _entities.at(j);
			try {
				Player *p = dynamic_cast<Player *>(e);
				if (p != nullptr) {
					if (p->isAlive() || p->HP > 0) {
						pAlive++;
					}
				}
			}
			catch (const std::bad_cast& cast) {
			}
		}
	}
	if (pAlive <= 1) {
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::GameEnd));
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::LastManStanding));
		gameState = GameCurrentState::ENDED;
	}
	/*
	if (_totalDT >= GAME_TIME_LIMIT_MAXIMUM) {
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::GameEnd));
		StateManager::getInstance().eventManager.queueEvent(Event(EventType::TimeLimit));
		gameState = GameCurrentState::ENDED;
	}
	*/
}

void GameLogic::addEntityIDToDelete(int id){
	_idsToDestroy.push(id);
}

void GameLogic::_emptyAllEntities()
{
	for (int i = _entities.size() - 1; i >= 0; i--) {
		Entity* e = _entities.at(i);
		if (e != nullptr) {
			delete e;
		}
	}
}

void GameLogic::addEntity(Entity *e) {
	_entities.push_back(e);
}

Entity* GameLogic::findEntity(int id) {
	for (int i = 0;  i < _entities.size(); i++) {
		if (_entities.at(i)->getID() == id) {
			return _entities.at(i);
		}
	}
	return nullptr;
}

Entity& GameLogic::findEntityCopy(int id) {
	for (int i = 0; i < _entities.size(); i++) {
		if (_entities.at(i)->getID() == id) {
			return *_entities.at(i);
		}
	}
	Entity e;
	return e;
}

Player& GameLogic::findPlayer(int id) {
	for (int i = 0; i < _entities.size(); i++) {
		Entity *e = _entities.at(i);
		if (e->getID() == id) {
			try{
				Player *p = dynamic_cast<Player *>(e);
				return *p;
			}
			catch (const std::bad_cast& cast){
			}
		}
	}

}

Player * GameLogic::getPlayer(int playerNumber){
	int id = _playerIDs.at(playerNumber - 1);
	for (int i = 0; i < _entities.size(); i++) {
		Entity *e = _entities.at(i);
		if (e->getID() == id) {
			try{
				Player *p = dynamic_cast<Player *>(e);
				return p;
			}
			catch (const std::bad_cast& cast){
			}
		}
	}
}

Player GameLogic::getPlayerCopy(int playerNumber){
	int id = _playerIDs[playerNumber - 1];
	for (int i = 0; i < _entities.size(); i++) {
		Entity *e = _entities.at(i);
		if (e->getID() == id) {
			try{
				Player *p = dynamic_cast<Player *>(e);
				return *p;
			}
			catch (const std::bad_cast& cast){
			}
		}
	}
}

void GameLogic::_spawnItems()
{
}

void GameLogic::_spawnEnergy()
{
	for (int i = 0; i < _spawnPoints.size(); i++) {
		Vector2 v = _spawnPoints.at(i);
		Energy *e{ new Energy(v, GAME_ENERGY_SPAWN_AURA) };
		addEntity(e);
	}
}

void GameLogic::_spawnPowerUps()
{
}
