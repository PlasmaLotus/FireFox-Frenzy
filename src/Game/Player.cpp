#include <math.h>
#include <cmath>
#include "Player.h"
#include "../Main.h"
//#include "../States/StateManager.h"

Player::Player() :
MovingEntity() {
	posX = 10.f;
	posY = 10.f;
	posZ = 10.f;
	velocityX = 1.f;
	velocityY = 1.f;
	orientation = 0.f;
	orientationX = 0.f;
	orientationY = 0.f;
	cursorOrientation = 0.f;
	cursorOrientationX = 0.f;
	cursorOrientationY = 0.f;
}

Player::~Player()
{
}

void Player::update(int dt)
{
	
	prevPosX = posX;
	prevPosY = posY;
	prevPosZ = posZ;
	/*
	posX += velocityX;
	posY += velocityY;
	posZ += velocityZ;
	*/
	float speedX = 0.f;
	float speedY = 0.f;

	//if (orientation)
	//posX += std::sin(orientation) * dt * velocityX;
	//posY += std::cos(orientation) * dt * velocityY;
	posX += std::sin(orientation) *std::abs(orientationX)/10 * velocityX;
	posY += std::cos(orientation)  *std::abs(orientationY)/10 * velocityY;
	printf("posX: %3.2f - posY: %3.2f\n", posX, posY);
	printf("TickX: %3.4f -- TickY: %3.4f\n", std::sin(orientation) * velocityX, std::cos(orientation)  * velocityY);
	//	; Math.sin(direction) * dt * velocityX;
	//basicBlock.y += Math.cos(direction) * dt * speed;

}

void Player::setPlayerOrienation(float x, float y)
{
	orientation = std::atan2(x, y);
	orientationX = x;
	orientationY = y;
		///= tan–1(y / x)
	printf("PlayerAngle: %3.3f, %3.3f\n", x, y);
	printf("PlayerAngle: %3.3f\n", orientation);
}

void Player::setCursorOrientation(float x, float y)
{

	cursorOrientation = std::atan2(x, y);
	cursorOrientationX = x;
	cursorOrientationY = y;
	printf("CursorAngle: %3.3f, %3.3f\n", x, y);
	printf("CursorAngle: %3.3f\n", cursorOrientation);
}

void Player::setCursorOrientationFromMouse(int x, int y)
{
	printf("MousePos: %d, %d\n", x, y);
	setCursorOrientation( x - posX , y - posY);
}
