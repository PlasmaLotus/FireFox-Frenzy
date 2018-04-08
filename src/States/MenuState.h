#ifndef __MenuState__
#define __MenuState__

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
	MenuState(Menu * m);
	virtual void tick(int dt, bool render = true);
	virtual ~MenuState();

	Menu* menu;
	ControllerConfig* p1KeyConfig;
	Controller *p1Controller;
	ControllerConfig* p2KeyConfig;
	Controller *p2Controller;
	sf::RenderWindow *window;
	/**/
	MenuRenderer *renderer;
};

#endif //!__MenuState__