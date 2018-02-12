#pragma once


/*
Created by PlasmaLotus
Updated Feb 11, 2018
*/

#include <SFML\Graphics.hpp>

//#include "Renderer.h"

#ifndef __Player_Drawable__
#define __Player_Drawable__

#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Game/Player.h"

class PlayerDrawable : public sf::Drawable {
public:


	PlayerDrawable();
	PlayerDrawable(Player *player);
	~PlayerDrawable();


	// H�rit� via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	Player *player;
	int posX;
	int posY;
	int width;
	int height;
	sf::RectangleShape playerShape;
	sf::CircleShape cursorShape;

};

#endif // !__Player_Renderer__
