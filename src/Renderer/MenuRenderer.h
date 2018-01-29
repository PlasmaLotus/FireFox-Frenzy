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

class MenuRenderer : public Renderer{
public:

	void render();
	void clear();
	void draw();

	void display();
	void addMenu(Menu *m);
	void addWindow(sf::RenderWindow * g);
	sf::Texture getLastFrame();

	MenuRenderer();
	MenuRenderer(sf::RenderWindow* window, Menu* m);
	~MenuRenderer();
	//void setBoards(Board b1, Board b2);
	
	bool initRenderer();

	sf::RenderWindow* window;
	Menu* menu;

	sf::Texture lastFrame;//not implemented
	sf::Text debugText;
	bool texturesLoaded = false;
	const float ok = 100.f;
	//sf::CircleShape shape(ok);
	sf::CircleShape shape;
	sf::RectangleShape menuItems[10];
	int nbMenuItems;

	//MenuItemDrawable test;
};

#endif // __Menu_Renderer__
