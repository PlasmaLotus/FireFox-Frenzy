#pragma once
/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Game_Logic_
#define _Game_Logic_

#include <stdint.h>
#include <vector>
#include <stack>
#include "Entity.h"
#include "Player.h"
#include "Projectile.h"
enum GameCurrentState{RUNNING, PAUSED, ENDED};

class GameLogic{
	
public:
	int frame = 0;
	int32_t dt;
	GameCurrentState gameState;

	GameLogic();
	~GameLogic();
	void init();
	void reset();
	void tick();
	void pause();
	void addEntity(Entity* e);
	Entity &findEntity(int id);
	Player &findPlayer(int id);
	Entity findEntityCopy(int id);
	//Player &findPlayer(int id);
	static const int NB_PLAYERS{ 2 };
	Player *getPlayer(int playerNumber);
	Player getPlayerCopy(int playerNumber);
	//Player p1;
	//Player p2;
	//Player p3;
	//Player p4;
	//std::vector<Player> _otherPlayers;
	//std::vector<Player> _players;
	Player __otherPlayers[NB_PLAYERS -1];
	//Vector
	std::vector<Vector2> _spawnPoints;
	std::vector<int> _playerIDs;
	int __playerIDs[4]{ -1 };
	std::vector<Entity *> _entities;
	//std::vector<Entity*> __entities;
	//std::vector<Projectile> _projectiles;
	std::stack<int> _idsToDestroy;
	void _handleEntitiesUpdate(int32_t dt);
	void _handleEntitiesCollisions(int32_t dt);
	void _handleEntitiesCollisions_Players(int32_t dt);
	void _handleEntitiesCollisions_PlayersToProjectiles(int32_t dt);
	void _handleEntitesEnd();
	void addEntityIDToDelete(int id);
	static const int PROJECTILE_COLLISION_DELAY_GENERAL = 60;

	static const int PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME = 2000;
	static const int PLAYER_PROJECTILE_MAXIMUM_ENERGY_COST = 100;
	static const int PLAYER_PROJECTILE_MINIMUM_ENERGY_COST = 5;
	static const int PLAYER_COLLISION_HITBOX_WIDTH = 30;
	static const int PLAYER_COLLISION_HITBOX_HEIGHT = 35;
	static int const AMMO_RECHARGE_COOLDOWN{ 3500 }; //as miliseconds
	static int const MAX_AMMO{ 10 };
	static float const PLAYER_MAX_VELOCITY;
	static float const PLAYER_MAX_VELOCITY_DECREASE_RATE;
	static float const PLAYER_FRICTION;
	static float const PLAYER_VELOCITY_DEAD_ZONE;
	static float const PLAYER_ACCELERATION_RATE;
	static float const PLAYER_SHIELD_RADIUS;
private:
	void _emptyAllEntities();

};

#endif // !_Game_

