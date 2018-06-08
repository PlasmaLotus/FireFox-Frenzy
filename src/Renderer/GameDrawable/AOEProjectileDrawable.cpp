#include "AOEProjectileDrawable.h"
#include "../../Game/GameLogic.h"


AOEProjectileDrawable::AOEProjectileDrawable(AOEProjectile * pj, sf::Texture& tx) :
	ProjectileDrawable(pj, tx),
	aoeProjectile(pj)
{
}

AOEProjectileDrawable::~AOEProjectileDrawable(){
}

void AOEProjectileDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (aoeProjectile->m_mainProjectileActive) {
		if (posX + aoeProjectile->width / 2.f >= mViewCenter.x - mViewSize.x / 2.f && posX - aoeProjectile->width / 2.f <= mViewCenter.x + mViewSize.x / 2.f) {
			if (posY + aoeProjectile->height / 2.f >= mViewCenter.y - mViewSize.y / 2.f && posY - aoeProjectile->height / 2.f <= mViewCenter.y + mViewSize.y / 2.f) {
				target.draw(m_sprite);
				if (_displayHitboxes) {
					target.draw(projectileHitboxShape);
				}
			}
		}
	}

	for (int i = aoeProjectile->m_projectiles.size() - 1; i >= 0; --i) {
		Projectile& p{ aoeProjectile->m_projectiles.at(i) };
		
		if (p.posX + p.width / 2.f >= mViewCenter.x - mViewSize.x / 2.f && p.posX - p.width / 2.f <= mViewCenter.x + mViewSize.x / 2.f) {
			if (p.posY + p.height / 2.f >= mViewCenter.y - mViewSize.y / 2.f && p.posY - p.height / 2.f <= mViewCenter.y + mViewSize.y / 2.f) {
				
				
				sf::CircleShape c;//hitbox
				c.setRadius(p.width / 2);
				c.setFillColor(sf::Color::Red);
				c.setOrigin(c.getRadius(), c.getRadius());
				c.setPosition(sf::Vector2f(p.posX, p.posY));
				target.draw(c);
			}
		}

	}
}

void AOEProjectileDrawable::update(){
	posX = aoeProjectile->posX;
	posY = aoeProjectile->posY;

	projectileHitboxShape.setPosition(sf::Vector2f(1.0f *posX - projectile->width / 2, 1.0f*posY - projectile->height / 2));
	/*Withouth set Origin*/
	//sprite.setPosition(sf::Vector2f(posX - sprite.getGlobalBounds().width / 2, posY - sprite.getGlobalBounds().height / 2));
	m_sprite.setPosition(sf::Vector2f(posX, posY));

	if (projectile->orientation == 0.f) {
	}
	else {
		angleDeg = std::atan2(projectile->orientationX, -projectile->orientationY) * 180 / (atan(1) * 4);
	}

	m_sprite.setRotation(angleDeg);
	m_sprite.setColor(projectileColor);

}
