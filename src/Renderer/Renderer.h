#pragma once


#include <SFML\Window.hpp>

#ifndef _Renderer_
#define _Renderer_

class Renderer
{
public:
	Renderer();
	//Renderer(sf::RenderWindow* window);
	virtual ~Renderer();

	virtual void render();
	virtual void clear();
	virtual void draw();
	virtual void display();

	//sf::RenderWindow* window;
};

#endif