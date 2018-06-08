#include "GameItemDrawable.h"
#include "../../Game/GameLogic.h"

GameItemDrawable::GameItemDrawable(Item * pj, sf::Texture& tx):
	GameDrawable(),
	item(pj),
	m_texture(tx)
{
	posX = item->posX;
	posY = item->posY;
	radius = item->width*2;
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(1.0f * m_sprite.getGlobalBounds().width / 2, 1.0f * m_sprite.getGlobalBounds().height / 2));
	m_sprite.setScale(sf::Vector2f(1.0f* radius / m_texture.getSize().x, 1.0 * radius / m_texture.getSize().y));
	itemColor = m_sprite.getColor();
	itemHitboxColor = sf::Color::Blue;
}

GameItemDrawable::~GameItemDrawable(){
}

void GameItemDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (_inView) {
		target.draw(m_sprite);
		if (_displayHitboxes) {
			target.draw(itemHitboxShape);
		}
	}
}

void GameItemDrawable::update(){
	posX = item->posX;
	posY = item->posY;
	/*Withouth set Origin*/
	//sprite.setPosition(sf::Vector2f(posX - sprite.getGlobalBounds().width / 2, posY - sprite.getGlobalBounds().height / 2));
	m_sprite.setPosition(sf::Vector2f(posX, posY));
	itemHitboxShape.setPosition(sf::Vector2f(1.0f *posX - item->width / 2, 1.0f*posY - item->height / 2));
	if (item->state != ItemState::ItemActive) {
		sf::Color c(itemColor);
		c.a = 50;
		m_sprite.setColor(c);
		itemHitboxColor = sf::Color::Cyan;
	}
	else {
		m_sprite.setColor(itemColor);
		itemHitboxColor = sf::Color::Blue;
	}
	itemHitboxShape.setFillColor(itemHitboxColor);

	_inView = false;
	if (posX + item->width / 2.f >= mViewCenter.x - mViewSize.x / 2.f && posX - item->width / 2.f <= mViewCenter.x + mViewSize.x / 2.f) {
		if (posY + item->height / 2.f >= mViewCenter.y - mViewSize.y / 2.f && posY - item->height / 2.f <= mViewCenter.y + mViewSize.y / 2.f) {
			_inView = true;
		}
	}
}
