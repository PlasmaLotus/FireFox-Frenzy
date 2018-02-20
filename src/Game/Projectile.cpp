#include "Projectile.h"

Projectile::Projectile(): MovingEntity(){

}

Projectile::~Projectile(){

}

void Projectile::update(int dt)
{
	prevPosX = posX;
	prevPosY = posY;
	prevPosZ = posZ;
	float speedX = 0.f;
	float speedY = 0.f;

	//posX += std::sin(orientation) * dt * velocityX;
	//posY += std::cos(orientation) * dt * velocityY;
	posX += std::sin(orientation) * velocityX;
	posY += std::cos(orientation) * velocityY;
	lifetime--;
}

