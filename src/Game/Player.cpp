#include <math.h>
#include <cmath>
#include "Player.h"
#include "../Main.h"
//#include "../States/StateManager.h"

Player::Player() :
SquareEntity() {
	state = PlayerState::Moving;
	posX = 10.f;
	posY = 10.f;
	//posZ = 10.f;
	velocityX = 1.f;
	velocityY = 1.f;
	orientation = 0.f;
	orientationX = 0.f;
	orientationY = 0.f;
	cursorOrientation = 0.f;
	cursorOrientationX = 0.f;
	cursorOrientationY = 0.f;
	dashVelocity = 2.0f;
	dashMaxDuration = 20;
	dashTime = 0;
}

Player::~Player()
{
	projectiles.empty();
}

void Player::update(int dt)
{
	/*Movement*/
	prevPosX = posX;
	prevPosY = posY;
	//prevPosZ = posZ;
	/*
	posX += velocityX;
	posY += velocityY;
	posZ += velocityZ;
	*/
	float speedX = 0.f;
	float speedY = 0.f;

	printf("PLAYER STATE:: %d\n", state);
	switch (state) {
	case::PlayerState::Moving: {
		//if (orientation)
		//posX += std::sin(orientation) * dt * velocityX;
		//posY += std::cos(orientation) * dt * velocityY;
		posX += std::sin(orientation) *std::abs(orientationX) / 10 * velocityX;
		posY += std::cos(orientation)  *std::abs(orientationY) / 10 * velocityY;
		printf("posX: %3.2f - posY: %3.2f\n", posX, posY);
		//printf("TickX: %3.4f -- TickY: %3.4f\n", std::sin(orientation) * velocityX, std::cos(orientation)  * velocityY);
		//	; Math.sin(direction) * dt * velocityX;
		break;
	}
	case::PlayerState::Dashing: {
		dashTime--;

		posX += std::sin(dashOrientation) * (50) / 10 * dashVelocity;
		posY += std::cos(dashOrientation) * (50) / 10 * dashVelocity;

		if (dashTime <= 0){
			state = PlayerState::Moving;
		}
		break;
	}
	}
	


	/*Projectiles*/
	shootHeld = false;
	shootTime--;
	if (shootTime <= 0) {
		canShoot = true;
	}
	for (std::vector<Projectile>::iterator it = projectiles.begin(); it != projectiles.end(); it++) {
		it->update(dt);
		if (it->durability <= 0) {
			projectiles.erase(it);
		}
	}
	/*
	for (int i = projectiles.size() -1; i >= 0 ; i--) {
		projectiles.at(i).update(dt);
		if (projectiles.at(i).durability <= 0) {
			projectiles.erase(projectiles.begin() + i);
		}
	}
	*/
}

void Player::setPlayerOrienation(float x, float y)
{
	orientation = std::atan2(x, y);
	orientationX = x;
	orientationY = y;
}

void Player::setCursorOrientation(float x, float y)
{
	cursorOrientation = std::atan2(x, y);
	cursorOrientationX = x;
	cursorOrientationY = y;
}

void Player::setCursorOrientationFromMouse(int x, int y)
{
	printf("MousePos: %d, %d\n", x, y);
	setCursorOrientation( x - posX , y - posY);
}

void Player::shoot() {
	//shootTime--;
	//shootTime <= 0
	if (canShoot && !shootHeld) {
		Projectile p;
		p.durability = 1;
		p.lifetime = 300;
		p.orientation = cursorOrientation;
		p.posX = posX;
		p.posY = posY;
		p.velocityX = 10.f;
		p.velocityY = 10.f;

		projectiles.push_back(p);
		
	}
	canShoot = false;
	shootHeld = true;
	shootTime = SHOOT_COOLDOWN;

	printf("SHOOTING: shootTime: %d,  --  nbProjectiles %d \n", shootTime, projectiles.size());
}

void Player::dash() {
	if (state == PlayerState::Moving){
		state = PlayerState::Dashing;

		dashOrientation = orientation;
		dashOrientationX = orientationX;
		dashOrientationY = orientationY;
		dashTime = dashMaxDuration;

	}
}