#pragma once
/*
Created by PlasmaLotus
Updated Dec 29, 2019
*/

//#include "Renderer.h"

#ifndef __Menu_Item_Drawable__
#define __Menu_Item_Drawable__

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Menu/MenuItem.h"

class MenuItemDrawable : public sf::Drawable {
public:

	MenuItemDrawable();
	MenuItemDrawable(MenuItem *menuItem, int px, int py);
	~MenuItemDrawable();
	
	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	MenuItem *item;
	int posX;
	int posY;
	int width;
	int height;
	sf::RectangleShape shape;
	//std::string str1;
	//std::string str2;
	bool _isSelected;
	void isSelected(bool value);
	/*
	sf::Font* _font;
	sf::Font font;
	*/
	void setFont(sf::Font & f);
	/*
	sf::Text s1;
	sf::Text s2;
	*/
	sf::Font m_font;
	sf::Text m_menuItemText;
	sf::Text m_menuItemText2;
};

#endif // !__Game_Renderer__