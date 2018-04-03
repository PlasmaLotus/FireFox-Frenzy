/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Game_Controller_H_
#define _Game_Controller_H_

#include "Controller.h"
#include "../Game/Player.h"
#include "../States/State.h"

//enum MenuCommands{};

class GameController : public Controller {
public:
	GameController(ControllerConfig* config, Player* entity);
	GameController(State *state, ControllerConfig* config, Player* entity);
	~GameController();
	bool handleInput();
	void handleJoystickAxis(sf::Joystick::Axis axis);
	void handleMouseAxis();
	void setPlayer(Player* e);
private:
	Player *player;
	State *state;
	void handleCommand(ControllerCommand command);
	float pAngleX;
	float pAngleY;
	float cAngleX;
	float cAngleY;
};

#endif // _Controller_H_
