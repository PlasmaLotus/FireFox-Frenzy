#include "MapDrawable.h"
#include "../../States/StateManager.h"
#include "../../Game/GameLogic.h"
#include <math.h>

MapDrawable::MapDrawable():
	MapDrawable(nullptr){
}
MapDrawable::MapDrawable(Map *map) :
	GameDrawable(),
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
	mapShape.setSize(sf::Vector2f(m_map->width, m_map->height));

}
MapDrawable::~MapDrawable() {
}

void MapDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const{

	target.draw(mapShape);
	//	for (const Entity& wall : m_map->_walls)
	for (int i= m_map->_walls.size()-1; i >= 0; --i){

		Entity* wall{ m_map->_walls.at(i) };

		//Test if wall is in the view
		/*
		float pos1X = wall->posX + wall->width / 2.f;
		float viewPos1X = mViewCenter.x - mViewSize.x / 2.f;

		float pos2X = wall->posX - wall->width / 2.f;
		float viewPos2X = mViewCenter.x + mViewSize.x / 2.f;
		*/


		if (wall->posX + wall->width / 2.f >= mViewCenter.x - mViewSize.x / 2.f && wall->posX - wall->width / 2.f <= mViewCenter.x + mViewSize.x / 2.f) {
			if (wall->posY + wall->height / 2.f >= mViewCenter.y - mViewSize.y / 2.f && wall->posY - wall->height / 2.f <= mViewCenter.y + mViewSize.y / 2.f) {
				//Draw Wall
				CircleEntity * ce = dynamic_cast<CircleEntity*>(wall);
				SquareEntity * se = dynamic_cast<SquareEntity*>(wall);

				if (ce != nullptr) {
					sf::CircleShape wallShape;
					wallShape.setOutlineColor(sf::Color::White);
					wallShape.setOutlineThickness(5.0f);
					wallShape.setFillColor(sf::Color(0, 0, 0, 0));
					wallShape.setRadius(wall->width / 2);
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
		
	}
}


void MapDrawable::update(){
	//mapShape.setPosition(sf::Vector2f(0.f, 0.f));
	//mapShape.setSize(sf::Vector2f(m_map->width, m_map->height));
}
