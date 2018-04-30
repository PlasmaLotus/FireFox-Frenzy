
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
#include "../Game/Map.h"
#include <vector>

class MapDrawable : public sf::Drawable {
public:

	MapDrawable();
	MapDrawable(Map * map);
	~MapDrawable();

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	Map *m_map;
	int width;
	int height;
	sf::Color mapColor;
	sf::RectangleShape mapShape;

};


#endif // !__Player_Renderer__
