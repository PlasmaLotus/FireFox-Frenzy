#pragma once

#ifndef __PLAYER__
#define __PLAYER__
#include <math.h>
#include "SquareEntity.h"
#include "Projectile.h"
#include <stdint.h>
#include <vector>
#include <cmath>
class GameLogic;
enum PlayerState{ ShootWindup, Shooting, ShootCooldown, Moving, Dashing};
class Player: public SquareEntity{
public:
	Player();
	Player(GameLogic *g);
	//Player & operator= (const Player &) = default;
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
	void shoot();
	//void chargeShooting();
	void dash();
	void shield();
	void move(float x, float y);
	void setPlayerOrienation(float x, float y);
	void setCursorOrientation(float x, float y);

	void _gainAmmo(int nb);
	void _loseAmmo(int nb);
	//std::vector <Projectile> projectiles;
	//void update();
	
	void setCursorOrientationFromMouse(int x, int y);
	bool testCollision(Entity e);
	bool testCollision(SquareEntity e);
	bool testCollision(CircleEntity e);
	void handleCollision();
	void _handleCollision(Projectile p);
	void handleCollision(Entity *e);
	bool collidableWith(Entity e);
	bool collidableWith(Projectile e);
	bool collidableWith(Player e);
	int HP = 100;
	bool _moveEngaged = false;
	/*Shooting*/
	int const SHOOT_COOLDOWN {10};
	bool shootHeld{ false };
	bool _shootHeld{ false };
	int shootCooldownTime{ 0 };
	bool canShoot{ true };
	//bool _chargingShooting;
	int _shotChargeHeldTime{ 0 };
	int __shotChargeInitialCooldown{ 5 };
	void _handleMovement(int dt);
	
	/*Dash*/
	float dashVelocity;
	int dashMaxDuration;
	int dashTime;
	float dashOrientation;
	float dashOrientationX;
	float dashOrientationY;

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
	/*Shield*/
	Projectile _shield;
	bool shieldActive;
	bool _shieldActive;
	int _shieldActiveDuration;
	void handleShield(int dt);
	//protected:
};
#endif // !__PLAYER__