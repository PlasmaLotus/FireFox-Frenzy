#pragma once

/*
Created by PlasmaLotus
Updated May 17, 2017
*/ 

#ifndef _MenuState_
#define _MenuState_

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "State.h"
#include "../Menu/Menu.h"
#include "../Controller/MenuController.h"
#include "../Controller/ControllerConfig.h"
#include "../Renderer/MenuRenderer.h"
//#include "../Main.h"

class MenuState :public State
{
public:
	MenuState();
	MenuState(sf::RenderWindow * w, Menu *m);
	MenuState(sf::RenderWindow *w);
	virtual void tick();
	virtual ~MenuState();

	Menu* menu;
	ControllerConfig* p1KeyConfig;
	Controller *p1Controller;
	sf::RenderWindow *window;
	/**/
	MenuRenderer *renderer;
};

#endif

