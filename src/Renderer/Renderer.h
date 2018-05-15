#pragma once
#include <SFML\Window.hpp>
#ifndef _Renderer_
#define _Renderer_
class Renderer
{
public:
	Renderer();
	virtual ~Renderer();
	virtual void render();
protected:
	virtual void clear();
	virtual void draw();
	virtual void display();
	virtual void update();
};

#endif