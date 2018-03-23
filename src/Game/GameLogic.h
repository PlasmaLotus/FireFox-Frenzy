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
enum GameCurrentState { RUNNING, PAUSED, ENDED, COUNTDOWN };

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
	Entity *findEntity(int id);
	Player &findPlayer(int id);
	Entity &findEntityCopy(int id);
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
	static const int PLAYER_COLLISION_HITBOX_WIDTH = 20;
	static const int PLAYER_COLLISION_HITBOX_HEIGHT = 30;
	static int const PLAYER_AMMO_RECHARGE_COOLDOWN{ 25 }; //as miliseconds
	static int const PLAYER_MAX_AMMO{ 1000 };

	static const int PLAYER_DASH_DURATION{ 150 };
	static const int PLAYER_DASH_RECHARGE_COOLDOWN{ 250 };
	static const int PLAYER_DASH_MAX_AMMO{ 3 };

	static float const PLAYER_MAX_VELOCITY;
	static float const PLAYER_MAX_VELOCITY_DECREASE_RATE;
	static float const PLAYER_FRICTION;
	static float const PLAYER_VELOCITY_DEAD_ZONE;
	static float const PLAYER_ACCELERATION_RATE;
	static float const PLAYER_DASH_VELOCITY;
	static const float PLAYER_MAX_VELOCITY_CAP_DECREASE_RATE;
	static const int GAME_COUNTDOWN_TIME{ 3000 };
	int countdownTimer = GAME_COUNTDOWN_TIME;
	int _countdownIt;

	static const int PROJECTILE_COLLISION_DELAY_GENERAL{ 30 };
	static const float PLAYER_SHIELD_RADIUS;

	static const int PLAYER_PROJECTILE_MAXIMUM_ENERGY_COST{ 100 };
	static const int PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME{ 2500 };
private:
	void _emptyAllEntities();

	

};

#endif // !_Game_

