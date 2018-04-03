/*
Created by PlasmaLotus
Updated May 13, 2017
*/
#ifndef _Menu_Controller_H_
#define _Menu_Controller_H_

#include "Controller.h"
#include "../Menu/Menu.h"

class MenuController : public Controller {
public:
	MenuController(ControllerConfig* config, Menu* menu);
	~MenuController();
	void setMenu(Menu* b);
	void handleJoystickAxis(sf::Joystick::Axis axis);
	void handleMouseAxis();
private:
	Menu* menu;
	ControlMode mode;
	void handleCommand(ControllerCommand command);
};

#endif // _Controller_H_
