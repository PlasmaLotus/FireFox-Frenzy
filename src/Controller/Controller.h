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
	virtual void handleInput();
	void __handleInput();
	void handleInputKeyboard();
	void handleInputJoystick();
	void viewDebugJoystick();
	void handleInputMouse();
	ControllerConfig * getConfig();
	ControlMode mode;
	ControllerConfig* config;
	virtual void handleCommand(ControllerCommand command);
	//virtual void handleCommand(ControllerCommand command, sf::Joystick::Axis axis, int position);// virtual
	virtual void handleJoystickAxis(sf::Joystick::Axis);
	virtual void handleMouseAxis();
	void swapToControlMode(ControlMode m);
	bool _swapConfig;
	ControlMode _nextMode;
	const int buttonHeldTimeLimit = 20;
	const int buttonHeldTimeMinimum = 0;
	bool buttonHeld[ControllerCommand::CommandMax] = { true };
	bool buttonUsedThisTick[ControllerCommand::CommandMax] = { false };
	int buttonHeldTime[ControllerCommand::CommandMax] = { buttonHeldTimeMinimum };
	int _buttonHeldTime[ControllerCommand::CommandMax] = { buttonHeldTimeMinimum };
	bool buttonCanBeHeld[ControllerCommand::CommandMax] = { false };
	bool keyboardConnected = true;
	bool joystickConnected = false;
};

#endif // _Controller_H_
