#pragma once
/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

//#include <SFML\Window.hpp>


#ifndef __Menu_Renderer__
#define __Menu_Renderer__

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Menu/Menu.h"
#include "Renderer.h"
#include "MenuItemDrawable.h"
#include <vector>
class MenuRenderer : public Renderer{
public:
	MenuRenderer();
	MenuRenderer(sf::RenderWindow* window, Menu* m);
	~MenuRenderer();
	virtual void render();
	virtual void clear();
	virtual void update();
	virtual void draw();
	virtual void display();

	virtual void addMenu(Menu *m);
	virtual void addWindow(sf::RenderWindow * g);
	sf::Texture getLastFrame();

protected:
	sf::Texture lastFrame;//not implemented
	bool texturesLoaded = false;
	const float ok = 100.f;
	sf::RectangleShape menuItems[10];
	std::vector<MenuItemDrawable> _menuItems;
	int nbMenuItems;
	bool fontLoaded{ true };
	sf::CircleShape shape;
	Menu* menu;
	sf::RenderWindow* window;
	virtual bool initRenderer();
	sf::Font font;
};

#endif // __Menu_Renderer__