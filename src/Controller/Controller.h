/*
Created by PlasmaLotus
Updated August 06, 2017
*/

#ifndef _Controller_H_
#define _Controller_H_

#include "SFML\Window.hpp"
#include "ControllerConfig.h"

class Controller {
public:
	Controller(ControllerConfig* c);
	~Controller();
	void updateConfig();
	void __updateConfig();
	void setControlMode(ControlMode mode);
	virtual bool handleInput();
	virtual void handleInputKeyboard();
	virtual void handleInputJoystick();
	void viewDebugJoystick();
	virtual void handleInputMouse();
	ControllerConfig * getConfig();
	ControlMode mode;
	ControllerConfig* config;
	virtual void handleCommand(ControllerCommand command);
	virtual void handleJoystickAxis(sf::Joystick::Axis);
	virtual void handleMouseAxis();
	void swapToControlMode(ControlMode m);
	bool _swapConfig;
	ControlMode _nextMode;
	bool buttonUsedThisTick[ControllerCommand::CommandMax] = { false };
	bool keyboardConnected = true;
	bool joystickConnected = false;
	bool commandPressed = false;
};

#endif // _Controller_H_
