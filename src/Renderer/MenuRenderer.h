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
	void render();
	void clear();
	void update();
	void draw();

	void display();
	void addMenu(Menu *m);
	void addWindow(sf::RenderWindow * g);
	sf::Texture getLastFrame();

	MenuRenderer();
	MenuRenderer(sf::RenderWindow* window, Menu* m);
	~MenuRenderer();
	bool initRenderer();

	sf::RenderWindow* window;
	Menu* menu;

	sf::Texture lastFrame;//not implemented
	//sf::Text debugText;
	//sf::Font font;
	bool texturesLoaded = false;
	const float ok = 100.f;
	//sf::CircleShape shape(ok);
	sf::CircleShape shape;
	sf::RectangleShape menuItems[10];
	std::vector<MenuItemDrawable> _menuItems;
	int nbMenuItems;
	bool fontLoaded{ true };
	//MenuItemDrawable test;
};

#endif // __Menu_Renderer__