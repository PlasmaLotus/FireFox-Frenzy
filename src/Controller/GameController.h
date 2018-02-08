/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Game_Controller_H_
#define _Game_Controller_H_

#include "Controller.h"
#include "../Game/Player.h"

//enum MenuCommands{};

class GameController : public Controller {
public:

	
	GameController(ControllerConfig* config, Player* entity);
	~GameController();
	void handleJoystickAxis(sf::Joystick::Axis axis);
	void handleMouseAxis();
	//void updateConfig();
	//void handleInput();
	void setPlayer(Player* e);
	//void handleInput();

	//void viewDebugJoystick();

private:
	Player *player;
	ControlMode mode;
	//ControllerConfig config;
	//ControllerConfig* config_;
	void handleCommand(ControllerCommand command);
	//bool buttonHeld[ControllerCommand::CommandMax];
	//int buttonHeldTime[ControllerCommand::CommandMax];
	//bool buttonCanBeHeld[ControllerCommand::CommandMax] = {false};
	//const int buttonHeldTimeLimit = 35;
};

#endif // _Controller_H_
