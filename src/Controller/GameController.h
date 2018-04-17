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
class GameState;
class GameController : public Controller {
public:
	GameController(ControllerConfig* config, Player* entity);
	GameController(GameState *state, ControllerConfig* config, Player* entity);
	~GameController();
	bool handleInput();
	void handleJoystickAxis(sf::Joystick::Axis axis);
	void handleMouseAxis();
	void setPlayer(Player* e);
	void setState(GameState* s);
private:
	Player *player;
	GameState *state;
	void handleCommand(ControllerCommand command);
	float pAngleX;
	float pAngleY;
	float cAngleX;
	float cAngleY;
};

#endif // _Controller_H_
