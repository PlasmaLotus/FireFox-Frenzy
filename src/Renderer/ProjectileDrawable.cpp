#include "ProjectileDrawable.h"
#include "../Game/GameLogic.h"

ProjectileDrawable::ProjectileDrawable()
{
}

ProjectileDrawable::ProjectileDrawable(Projectile * pj)
	:
	projectile(pj)
	//m_shaderLoaded(false)
{
	projectileHitboxShape.setFillColor(sf::Color(0, 255, 0, 150));
	projectileHitboxShape.setOutlineColor(sf::Color::Green);
	projectileHitboxShape.setOutlineThickness(2);
	float width = GameLogic::PROJECTILE_HITBOX_RADIUS_MINIMUM;
	projectileHitboxShape.setRadius(width);

	
	projectileColor = sf::Color::Green;
	posX = projectile->posX;
	posY = projectile->posY;
	radius = projectile->width;

	if (!m_texture.loadFromFile("./Assets/Images/Player_Shot.png")) {
		printf("Unable to load Player PNG\n");
	}

	if (!m_font.loadFromFile("./Assets/fonts/Minecraft.ttf")) {
		printf("Unable to load Minecraft Font\n");
	}
	

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(1.0f * m_sprite.getGlobalBounds().width / 2, 1.0f * m_sprite.getGlobalBounds().height / 2));
	m_sprite.setScale(sf::Vector2f(1.0f* radius / m_texture.getSize().x, 1.0 * radius / m_texture.getSize().y));
	
}


ProjectileDrawable::~ProjectileDrawable()
{
}

void ProjectileDrawable::setDisplayHitboxes(bool display)
{
	_displayHitboxes = display;
}

void ProjectileDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
	target.draw(projectileHitboxShape);
}

bool ProjectileDrawable::onLoad()
{
	return false;
}

void ProjectileDrawable::update()
{
	posX = projectile->posX;
	posY = projectile->posY;

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
}
