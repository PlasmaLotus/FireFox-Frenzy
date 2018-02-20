#include "PlayerDrawable.h"

PlayerDrawable::PlayerDrawable() {

}
PlayerDrawable::PlayerDrawable(Player *pl) :
player(pl){

	playerShape.setFillColor(sf::Color::Blue);
	playerShape.setSize(sf::Vector2f(10, 20));

	cursorShape.setFillColor(sf::Color::Cyan);
	cursorShape.setRadius(2);
}
PlayerDrawable::~PlayerDrawable() {

}

void PlayerDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(playerShape);
	target.draw(cursorShape);

	if (player->state == PlayerState::Dashing) {
		sf::RectangleShape dashShape;
		dashShape.setFillColor(sf::Color::Cyan);
		dashShape.setSize(sf::Vector2f(10, 20));
		dashShape.setPosition(sf::Vector2f(player->prevPosX, player->prevPosY));
		target.draw(dashShape);
	}

	for (std::vector<Projectile>::iterator it = player->projectiles.begin(); it != player->projectiles.end(); it++) {
		sf::CircleShape c(2);
		c.setFillColor(sf::Color::Blue);
		c.setOutlineColor(sf::Color::Red);
		c.setPosition(sf::Vector2f(it->posX, it->posY));
		target.draw(c);
	}
}

bool PlayerDrawable::onLoad()
{
	return false;
}

void PlayerDrawable::update()
{
	float pposX = player->posX;
	float pposY = player->posY;
	playerShape.setPosition(sf::Vector2f(pposX, pposY));
	cursorShape.setPosition(sf::Vector2f(pposX + player->cursorOrientationX, pposY + player->cursorOrientationY));
}
