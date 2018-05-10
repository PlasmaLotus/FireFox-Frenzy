#pragma once
/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

//#include <SFML\Window.hpp>


#ifndef __PauseMenu_Renderer__
#define __PauseMenu_Renderer__

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Menu/Menu.h"
#include "MenuRenderer.h"
#include "MenuItemDrawable.h"
#include <vector>
class  PauseMenuRenderer: public MenuRenderer {
public:
	void render();
	void clear();
	void update();
	void draw();
	void display();

	PauseMenuRenderer();
	PauseMenuRenderer(sf::RenderWindow* window, Menu* m);
	~PauseMenuRenderer();
	bool initRenderer();

	//sf::RenderWindow* window;
	//Menu* menu;

	//sf::Texture lastFrame;
	sf::Font font;
	bool texturesLoaded = false;
	float _windowHeight;
	float _windowWidth;
	sf::RectangleShape background;
	sf::RectangleShape foreground;
	//sf::RectangleShape menuItems[10];
	//std::vector<MenuItemDrawable> _menuItems;
	//int nbMenuItems;
	//bool fontLoaded{ true };
	//MenuItemDrawable test;
};

#endif // __Menu_Renderer__