/*
Created by PlasmaLotus
Updated Dec 29, 2019
*/

#include <SFML\Graphics.hpp>

#pragma once
//#include "Renderer.h"

#ifndef __Menu_Item_Drawable__
#define __Menu_Item_Drawable__

#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Menu/MenuItem.h"

class MenuItemDrawable : public sf::Drawable {
public:

	
	MenuItemDrawable();
	MenuItemDrawable(MenuItem *menuItem);
	~MenuItemDrawable();
	

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	void onUpdate(float time, float x, float y) ;
	void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	MenuItem *item;

};

#endif // !__Game_Renderer__
