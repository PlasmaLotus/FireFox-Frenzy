#include "ProjectileDrawable.h"
#include "../../Game/GameLogic.h"


ProjectileDrawable::ProjectileDrawable(Projectile * pj, sf::Texture& tx):
	GameDrawable(),
	projectile(pj),
	m_texture(tx)
	//m_shaderLoaded(false)
{
	projectileHitboxShape.setFillColor(sf::Color(0, 255, 0, 150));
	projectileHitboxShape.setOutlineColor(sf::Color::Green);
	projectileHitboxShape.setOutlineThickness(2);
	float width = pj->width;
	projectileHitboxShape.setRadius(width);

	projectileColor = sf::Color::Green;
	posX = projectile->posX;
	posY = projectile->posY;
	radius = projectile->width;

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(1.0f * m_sprite.getGlobalBounds().width / 2, 1.0f * m_sprite.getGlobalBounds().height / 2));
	m_sprite.setScale(sf::Vector2f(1.0f* radius / m_texture.getSize().x, 1.0 * radius / m_texture.getSize().y));
}


ProjectileDrawable::~ProjectileDrawable()
{
}

void ProjectileDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	float pos1X = posX + projectile->width / 2.f;
	float viewPos1X = mViewCenter.x - mViewSize.x / 2.f;

	float pos2X = posX - projectile->width / 2.f;
	float viewPos2X = mViewCenter.x + mViewSize.x / 2.f;


	if (posX + projectile->width / 2.f >= mViewCenter.x - mViewSize.x / 2.f && posX - projectile->width / 2.f <= mViewCenter.x + mViewSize.x / 2.f) {
		if (posY + projectile->height / 2.f >= mViewCenter.y - mViewSize.y / 2.f && posY - projectile->height / 2.f <= mViewCenter.y + mViewSize.y / 2.f) {
			target.draw(m_sprite);
			if (_displayHitboxes) {
				target.draw(projectileHitboxShape);
			}
		}
	}
	/*
	if (_inView) {
		target.draw(m_sprite);
		if (_displayHitboxes) {
			target.draw(projectileHitboxShape);
		}
	}
	*/
}

void ProjectileDrawable::update()
{
	posX = projectile->posX;
	posY = projectile->posY;

	projectileHitboxShape.setPosition(sf::Vector2f(1.0f *posX - projectile->width / 2, 1.0f*posY - projectile->height / 2));
	/*Withouth set Origin*/
	//sprite.setPosition(sf::Vector2f(posX - sprite.getGlobalBounds().width / 2, posY - sprite.getGlobalBounds().height / 2));
	m_sprite.setPosition(sf::Vector2f(posX, posY));

	if (!projectile->orientation == 0.f) {
		angleDeg = std::atan2(projectile->orientationX, -projectile->orientationY) * 180 / (atan(1) * 4);
	}
	m_sprite.setRotation(angleDeg);

	/*Check if projectile is in view*/
	/*
	_inView = false;
	if (posX + projectile->width / 2.f >= mViewCenter.x - mViewSize.x / 2.f && posX - projectile->width / 2.f >= mViewCenter.x + mViewSize.x / 2.f) {
		if (posY + projectile->height / 2.f >= mViewCenter.y - mViewSize.y / 2.f && posY - projectile->height / 2.f >= mViewCenter.y + mViewSize.y / 2.f) {
			_inView = true;
		}
	}
	*/

}

