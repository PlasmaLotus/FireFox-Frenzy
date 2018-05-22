/*
Created by PlasmaLotus
Updated 8 April, 2018
*/
#ifndef __PLAYER__
#define __PLAYER__

#include <math.h>
#include "SquareEntity.h"
#include "Projectile.h"
#include "Energy.h"
#include <stdint.h>
#include <vector>
#include <cmath>
#include "Powerup.h"
#include "PowerUpItem.h"
class GameLogic;
enum PlayerState{ ShootWindup, Shooting, ShootCooldown, Moving, Dashing, Shielding};
class Player: public SquareEntity{
public:
	Player();
	Player(GameLogic *g);
	Player(GameLogic *g, float x, float y);
	Player(GameLogic *g, Vector2 v);
	~Player();
	GameLogic * _game;
	void setGame(GameLogic *g);
	GameLogic* getGame();

	float orientationX;
	float orientationY;
	float cursorOrientation;
	float cursorOrientationX;
	float cursorOrientationY;

	bool isAlive();
	void update(int32_t dt);
	PlayerState state;
	void commandShootAlt();
	void commandDash();
	void commandShield();
	void commandMove(float x, float y);
	void setPlayerOrienation(float x, float y);
	void setCursorOrientation(float x, float y);
	void _gainAmmo(int nb);
	void _loseAmmo(int nb);

	void setCursorOrientationFromMouse(int x, int y);
	bool testCollision(Entity *e);

	void handleCollision();
	void _handleCollision(Projectile p);
	void _handleCollision(Energy e);
	//void _handleCollision(Enemy e);
	void _handleCollision(PowerUpItem p);
	void handleCollision(Entity *e);
	bool collidableWith(Entity* e);
	bool collidableWith(Projectile* e);
	bool collidableWith(Player* e);
	int HP;
	bool _moveEngaged = false;
	/*Shooting*/
	bool _autoFire{ true };
	bool shootHeld{ false };
	bool _shootHeld{ false };
	int shootCooldownTime{ 0 };
	bool canShoot{ true };
	int _shotChargeHeldTime{ 0 };

	//alt
	bool shootHeldAlt{ false };
	bool _shootHeldAlt{ false };
	int shootCooldownTimeAlt{ 0 };
	bool canShootAlt{ true };
	int _shotChargeHeldTimeAlt{ 0 };

	//int __shotChargeInitialCooldown{ 5 };
	void _handleMovement(int dt);
	
	/*Dash*/
	float dashVelocity;
	int dashMaxDuration;
	int dashTime;
	float dashOrientation;
	float dashOrientationX;
	float dashOrientationY;
	
	float dashAngle;
	float angleOrientation;
	float angleOrientationX;
	float angleOrientationY;
	void setDashOrientation(float x, float y);

	int const DASH_COOLDOWN{ 10 };
	bool canDash{ true };
	bool dashHeld{ true };
	bool _dashHeld{ true };
	int dashCooldownTime{ 0 };
	int _dashChargeHeldTime{ 0 };
	int __dashChargeInitialCooldown{ 5 };

	void handleDash(int dt);
	/*Projectile*/
	int32_t ammo;
	int32_t _ammoRechargeProgress; //as miliseconds
	void handleAmmo(int dt);
	void handleShooting(int dt);
	void handleShootingAlt(int dt);
	void _handleShooting(int power);
	void _handleShootingAlt(int power);
	/*Shield*/
	Projectile _shield;
	bool shieldActive;
	bool _shieldActive;
	int _shieldActiveDuration;
	void handleShield(int dt);

	/*Powerup*/
	PowerUp ability;
	void handleAbility(int dt);
};
#endif // !__PLAYER__