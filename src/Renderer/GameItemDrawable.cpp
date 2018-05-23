#include "GameItemDrawable.h"
#include "../Game/GameLogic.h"

/*
ProjectileDrawable::ProjectileDrawable()
{
}
*/
GameItemDrawable::GameItemDrawable(Item * pj, sf::Texture& tx):
	item(pj),
	m_texture(tx)
	//m_shaderLoaded(false)
{
	/*
	projectileHitboxShape.setFillColor(sf::Color(0, 255, 0, 150));
	projectileHitboxShape.setOutlineColor(sf::Color::Green);
	projectileHitboxShape.setOutlineThickness(2);
	float width = pj->width;
	projectileHitboxShape.setRadius(width);
	*/

	
	//projectileColor = sf::Color::Red;
	posX = item->posX;
	posY = item->posY;
	radius = item->width*2;
	//m_sprite.set
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(1.0f * m_sprite.getGlobalBounds().width / 2, 1.0f * m_sprite.getGlobalBounds().height / 2));
	m_sprite.setScale(sf::Vector2f(1.0f* radius / m_texture.getSize().x, 1.0 * radius / m_texture.getSize().y));
	//m_sprite.setColor(projectileColor);
}


GameItemDrawable::~GameItemDrawable()
{
}

/*
void GameItemDrawable::setDisplayHitboxes(bool display)
{
	_displayHitboxes = display;
}
*/

void GameItemDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

bool GameItemDrawable::onLoad()
{
	return true;
}

void GameItemDrawable::update()
{
	posX = item->posX;
	posY = item->posY;

	//projectileHitboxShape.setPosition(sf::Vector2f(1.0f *posX - projectile->width / 2, 1.0f*posY - projectile->height / 2));
	/*Withouth set Origin*/
	//sprite.setPosition(sf::Vector2f(posX - sprite.getGlobalBounds().width / 2, posY - sprite.getGlobalBounds().height / 2));
	m_sprite.setPosition(sf::Vector2f(posX, posY));


	//m_sprite.setColor(projectileColor);

}
