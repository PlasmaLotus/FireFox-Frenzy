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
const float GameLogic::PLAYER_DASH_VELOCITY(12.54f);
const float GameLogic::PLAYER_SHIELD_RADIUS(15.0f);
//const float GameLogic::PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME(2500);

GameLogic::GameLogic() :
	gameState(GameCurrentState::COUNTDOWN)
{

	init();
	//window.create(sf::VideoMode(800, 600), "SFML! Y U NO DRAW BLOCK!!");
}

GameLogic::~GameLogic(){
	_playerIDs.clear();
	//_projectiles.clear();
	//_players.clear();
	_emptyAllEntities();
	_entities.clear();
	//_otherPlayers.clear();
	_spawnPoints.clear();
	//_entities.clear();
}

void GameLogic::init() {
	//Player player(this);
	_spawnPoints.clear();
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
		Player *p1{ new Player(this) };
		Player *p2{ new Player(this) };
		Player *p3{ new Player(this) };
		Player *p4{ new Player(this) };
		Vector2 v1 = _spawnPoints.at(0);
		Vector2 v2 = _spawnPoints.at(1);
		Vector2 v3 = _spawnPoints.at(2);
		Vector2 v4 = _spawnPoints.at(3);
		p1->posX = v1.x;
		p1->posY = v1.y;
		p2->posX = v2.x;
		p2->posY = v2.y;
		p3->posX = v3.x;
		p3->posY = v3.y;
		p4->posX = v4.x;
		p4->posY = v4.y;

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
			//_countdownIt = 2;
			it = 2;
		}
		if (countdownTimer > GAME_COUNTDOWN_TIME / 3) {
			//_countdownIt = 1;
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

		//if (countdownTimer
		if (countdownTimer <= 0){
			gameState = GameCurrentState::RUNNING;
			countdownTimer = 0;
			StateManager::getInstance().eventManager.queueEvent(Event(EventType::CountdownStart));
		}
		break;
	case GameCurrentState::RUNNING:
		dt = StateManager::getInstance().getElapsedTime();
		printf("GameTick:  DT - %ld\n", dt);

		frame++;
		printf("MaxVelocity:%3.5f - Game Frame: %d\n", PLAYER_MAX_VELOCITY, frame);
		_handleEntitiesUpdate(dt);
		_handleEntitiesCollisions(dt);
		_handleEntitesEnd();
		//findEntity(2);
		break;
	default:
		break;
	}
	
}

void GameLogic::pause() {

}

void GameLogic::_handleEntitiesUpdate(int32_t dt)
{
	printf("Volume of Entities: %d,\n", _entities.size());
	for (int i = _entities.size() - 1; i >= 0; i--) {
		Entity *e = _entities.at(i);
		//_entities.at(i).update(dt);///////Out of Range
		e->update(dt);

		//Player Cast
		for (int pOffset = 0; pOffset < _playerIDs.size(); pOffset++) {
			if (e->getID() == _playerIDs.at(pOffset)) {
				try
				{
					Player *p = dynamic_cast<Player *>(e);
					//p.update(dt);
					printf("Player id-%d - HP:%d -  x:%3.2f - y:%3.2f | Ammo: %d/%d, %d/%d,\n", p->getID(), p->HP, p->posX, p->posY, p->ammo, PLAYER_MAX_AMMO, p->_ammoRechargeProgress, PLAYER_AMMO_RECHARGE_COOLDOWN);
					printf(" -- OriX:%3.2f - OriY:%3.2f | velocityX:%3.2f, velocityY:%3.2f\n", p->orientationX, p->orientationY, p->velocityX, p->velocityY);
					
					//e = static_cast<Entity &>(p);
				}
				catch (const std::bad_cast& cast)
				{
					//std::cerr << e.what() << std::endl;
					//std::cerr << "Cet objet n'est pas de type B" << std::endl;
				}
			}
		}
		
		if (!e->isAlive()) {
			addEntityIDToDelete(e->getID());
		}
	}
}

void GameLogic::_handleEntitiesCollisions(int32_t dt)
{
	for (int i = _entities.size() - 1; i >= 0; i--) {
		Entity *e1 = _entities.at(i);
		for (int j = _entities.size() - 1; j >= 0; j--) {
			Entity *e2 = _entities.at(j);
			if (e1 != e2) {
				if (e1->testCollision(*e2)) {
					e1->handleCollision(e2);
					printf("Collision Detected, ID:%d, ID:%d -  Distance: %3.3f!!!\n", e1->getID(), e2->getID(), e1->_distanceBetween(*e2));

				}
			}
		}
	}

	_handleEntitiesCollisions_Players(dt);
	_handleEntitiesCollisions_PlayersToProjectiles(dt);
}
void GameLogic::_handleEntitiesCollisions_Players(int32_t dt)
{
	/*
	Player &p1{ _players.at(0) };
	for (int i = _players.size() - 1; i >= 0; i--) {
		for (int j = _players.size() -1; j >= 0; j--) {
			Player &p2 = _players.at(j);
			if (p1.getID() != p2.getID()) {
				p1.testCollision(p2);
				if (p1.testCollision(p2)) {
					printf("Player Collision Detected!!!Distance: %3.3f\n", p1._distanceBetween(p2));
				}

				for (int k = p1.projectiles.size() - 1; k >= 0; k--) {
					Projectile &pro1 = p1.projectiles.at(k);
					
					//Enemy Projectiles
					for (int l = p2.projectiles.size() - 1; l >= 0; l--) {
						Projectile &pro2 = p2.projectiles.at(l);
						if (pro1.testCollision(pro2)) {
							printf("Projectile Collision Detected; Distance: %3.3f!!!\n", pro1._distanceBetween(pro2));
							//printf("P1: x:%3.3f - y:%3.3f ; P2: x:%3.3f - y:%3.3f", pro1.posX, pro1.posY, pro2.posX, pro2.posY);
						}
					}
				}
			}
		}
	}
	*/
}

void GameLogic::_handleEntitiesCollisions_PlayersToProjectiles(int32_t dt)
{
}

void GameLogic::_handleEntitesEnd()
{
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

void GameLogic::addEntityIDToDelete(int id)
{
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
			try
			{
				Player *p = dynamic_cast<Player *>(e);
				return *p;
			}
			catch (const std::bad_cast& cast)
			{
				//std::cerr << e.what() << std::endl;
				//std::cerr << "Cet objet n'est pas de type B" << std::endl;
			}
		}
	}

}

Player * GameLogic::getPlayer(int playerNumber)
{
	int id = _playerIDs.at(playerNumber - 1);
	for (int i = 0; i < _entities.size(); i++) {
		Entity *e = _entities.at(i);
		if (e->getID() == id) {
			try
			{
				Player *p = dynamic_cast<Player *>(e);
				return p;
			}
			catch (const std::bad_cast& cast)
			{
				//std::cerr << e.what() << std::endl;
				//std::cerr << "Cet objet n'est pas de type B" << std::endl;
			}
		}
	}
}

Player GameLogic::getPlayerCopy(int playerNumber)
{
	int id = _playerIDs[playerNumber - 1];
	for (int i = 0; i < _entities.size(); i++) {
		Entity *e = _entities.at(i);
		if (e->getID() == id) {
			try
			{
				Player *p = dynamic_cast<Player *>(e);
				return *p;
			}
			catch (const std::bad_cast& cast)
			{
				//std::cerr << e.what() << std::endl;
				//std::cerr << "Cet objet n'est pas de type B" << std::endl;
			}
		}
	}
}