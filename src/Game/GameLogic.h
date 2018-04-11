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
#include "Energy.h"
enum GameCurrentState { RUNNING, PAUSED, ENDED, COUNTDOWN };

class GameLogic{
public:
	int frame = 0;
	//int timer;
	int32_t dt;
	GameCurrentState gameState;

	GameLogic();
	~GameLogic();
	void reset();
	void tick(int dt);
	void pause();
	void addEntity(Entity* e);
	Entity *findEntity(int id);
	Player &findPlayer(int id);
	Entity &findEntityCopy(int id);
	static const int NB_PLAYERS{ 2 };
	Player *getPlayer(int playerNumber);
	Player getPlayerCopy(int playerNumber);

	Player __otherPlayers[NB_PLAYERS -1];
	std::vector<Vector2> _spawnPoints;
	std::vector<int> _playerIDs;
	int __playerIDs[4]{ -1 };
	std::vector<Entity *> _entities;
	std::stack<int> _idsToDestroy;
	void addEntityIDToDelete(int id);
	static const int PLAYER_COLLISION_HITBOX_WIDTH =32;
	static const int PLAYER_COLLISION_HITBOX_HEIGHT = 32;
	static int const PLAYER_AMMO_RECHARGE_COOLDOWN{ 500 }; //as miliseconds
	static int const PLAYER_MAX_AMMO{ 1000 };

	static const int PLAYER_DASH_DURATION{ 150 };
	static const int PLAYER_DASH_RECHARGE_COOLDOWN{ 250 };

	static float const PLAYER_MAX_VELOCITY;
	static float const PLAYER_MAX_VELOCITY_DECREASE_RATE;
	static float const PLAYER_FRICTION;
	static float const PLAYER_VELOCITY_DEAD_ZONE;
	static float const PLAYER_ACCELERATION_RATE;
	static float const PLAYER_DASH_VELOCITY;
	static float const PLAYER_MINIMUM_DASH_VELOCITY;
	static const float PLAYER_MAX_VELOCITY_CAP_DECREASE_RATE;
	static const int GAME_TIME_LIMIT_MAXIMUM{ 20000 };
	static const int GAME_COUNTDOWN_TIME{ 3000 };
	int countdownTimer = GAME_COUNTDOWN_TIME;
	int _countdownIt;
	int _totalDT;
	static const int PROJECTILE_COLLISION_DELAY_GENERAL{ 3000 };
	static const int PROJECTILE_COLLISION_DELAY_AOE{ 300 };
	static const float PROJECTILE_HITBOX_RADIUS_MINIMUM;
	static const float PROJECTILE_HITBOX_RADIUS_MAXIMUM;
	static const float PROJECTILE_SPEED_MINIMUM;
	static const float PROJECTILE_SPEED_MAXIMUM;
	static const float PLAYER_SHIELD_RADIUS;

	static const int PLAYER_PROJECTILE_MAXIMUM_ENERGY_COST{ 100 };
	static const int PLAYER_PROJECTILE_MAXIMUM_CHARGE_TIME{ 2500 };

	static const int PLAYER_SHOOT_COOLDOWN{ 7 };
	static const int PLAYER_DASH_MAXIMUM_ENERGY_COST{ 100 };
	static const int PLAYER_DASH_MAXIMUM_CHARGE_TIME{ 2000 };
	static const int PLAYER_DASH_MINIMUM_CHARGE_TIME{ 10 };

	static const float ENTITY_MINIMUM_RADIUS;
	static const float ENTITY_MINIMUM_WIDTH;
	static const float ENTITY_MINIMUM_HEIGHT;

	static const int ENERGY_MAX_AURA{ 100 };
	static const int ENERGY_MINIMUM_AURA{ 6 };
	static const float ENERGY_MAX_RADIUS;
	static const float ENERGY_MINIMUM_RADIUS;
	static const int ENERGY_ITEM_COOLDOWN{ 3000 };
	static const int ITEM_MINIMUM_COOLDOWN_TIME{ 1000 };
	static const int GAME_ENERGY_SPAWN_TIMER{ 20000 };
	static const int GAME_ENERGY_SPAWN_AURA{ 75 };

	static const int GAME_COLLISION_HITLAG{ 8 };
private:
	void init();
	void _emptyAllEntities();
	void _handleEntitesEnd();
	void _handleEntitiesUpdate(int32_t dt);
	void _handleEntitiesCollisions(int32_t dt);
	void _handleGameEnd();
	void _spawnItems();
	void _spawnEnergy();
	void _spawnPowerUps();
	int _spawnTimer;
};

#endif // !_Game_

