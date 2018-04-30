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
	mapShape.setPosition(sf::Vector2f(0.f, 0.f));
}
MapDrawable::~MapDrawable() {
}

void MapDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(mapShape);
	//	for (const Entity& wall : m_map->_walls)
	for (int i= m_map->_walls.size()-1; i >= 0; --i){
		Entity* wall{ m_map->_walls.at(i) };
		CircleEntity * ce = dynamic_cast<CircleEntity*>(wall);
		SquareEntity * se = dynamic_cast<SquareEntity*>(wall);
		if (ce != nullptr) {
			sf::CircleShape wallShape;
			wallShape.setOutlineColor(sf::Color::White);
			wallShape.setOutlineThickness(5.0f);
			wallShape.setFillColor(sf::Color(0, 0, 0, 0));
			wallShape.setRadius(wall->width/2);
			wallShape.setOrigin(wallShape.getGlobalBounds().width / 2.0f, wallShape.getGlobalBounds().height / 2.0f);
			wallShape.setPosition(wall->posX, wall->posY);
			target.draw(wallShape);
		}
		else if (se != nullptr) {
			sf::RectangleShape wallShape;
			wallShape.setOutlineColor(sf::Color::White);
			wallShape.setOutlineThickness(5.0f);
			wallShape.setFillColor(sf::Color(0, 0, 0, 0));
			wallShape.setSize(sf::Vector2f{ wall->width, wall->height });
			wallShape.setOrigin(wallShape.getGlobalBounds().width / 2.0f, wallShape.getGlobalBounds().height / 2.0f);
			wallShape.setPosition(wall->posX, wall->posY);
			target.draw(wallShape);
		}
		else {
			sf::RectangleShape wallShape;
			wallShape.setOutlineColor(sf::Color::White);
			wallShape.setOutlineThickness(5.0f);
			wallShape.setFillColor(sf::Color(0, 0, 0, 0));
			wallShape.setSize(sf::Vector2f{ wall->width, wall->height });
			wallShape.setOrigin(wallShape.getGlobalBounds().width / 2.0f, wallShape.getGlobalBounds().height / 2.0f);
			wallShape.setPosition(wall->posX, wall->posY);
			target.draw(wallShape);
		}

	}

}

bool MapDrawable::onLoad()
{
	return false;
}

void MapDrawable::update()
{
	//mapShape.setPosition(sf::Vector2f(0.f, 0.f));
	mapShape.setSize(sf::Vector2f(m_map->width, m_map->height));
	
}
