#include "MapDrawable.h"
#include "../States/StateManager.h"
#include "../Game/Shield.h"
#include "../Game/GameLogic.h"
#include <math.h>
MapDrawable::MapDrawable() {

}
MapDrawable::MapDrawable(Map *map) :
	sf::Drawable(),
	m_map(map)
{
	mapShape.setOutlineColor(sf::Color::White);
	mapShape.setFillColor(sf::Color(0,0,0,0));
	mapShape.setOutlineThickness(5.0f);
	int width = GameLogic::MAP_DEFAULT_WIDTH;
	int height = GameLogic::MAP_DEFAULT_HEIGHT;
	mapShape.setSize(sf::Vector2f(width, height));

	mapColor = sf::Color::White;

}
MapDrawable::~MapDrawable() {
}

void MapDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(mapShape);

	for (const Entity& wall : m_map->_walls) {
		sf::RectangleShape wallShape;
		wallShape.setOutlineColor(sf::Color::White);
		wallShape.setOutlineThickness(5.0f);
		wallShape.setFillColor(sf::Color(0, 0, 0, 0));
		wallShape.setSize(sf::Vector2f{ wall.width, wall.height });
		wallShape.setOrigin(wallShape.getGlobalBounds().width / 2.0f, wallShape.getGlobalBounds().height / 2.0f);
		wallShape.setPosition(wall.posX, wall.posY);
		target.draw(wallShape);

	}

}

bool MapDrawable::onLoad()
{
	return false;
}

void MapDrawable::update()
{
	mapShape.setPosition(sf::Vector2f(0.f, 0.f));
	
}
