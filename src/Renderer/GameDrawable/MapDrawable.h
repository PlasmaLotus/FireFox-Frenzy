
/*
Created by PlasmaLotus
Updated Feb 11, 2018
*/


#ifndef __MAP_Drawable__
#define __MAP_Drawable__
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include <string.h>
#include <string>
#include "../../Game/Map.h"
#include <vector>
#include "GameDrawable.h"

class MapDrawable : public GameDrawable {
public:

	MapDrawable();
	MapDrawable(Map * map);
	~MapDrawable();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void update();
	Map *m_map;
	int width;
	int height;
	sf::Color mapColor;
	sf::RectangleShape mapShape;

};


#endif // !__Player_Renderer__
