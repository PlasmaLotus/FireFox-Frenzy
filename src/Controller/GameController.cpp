/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameController.h"

/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute on the Board and Game*/


GameController::GameController(ControllerConfig* c, Player* e) :
Controller(c),
player(e),
mode(ControlMode::Joystick)
{
	//config.loadConfig("controllerConfig.ini");
	buttonCanBeHeld[ControllerCommand::Left] = true;
	buttonCanBeHeld[ControllerCommand::Right] = true;
	buttonCanBeHeld[ControllerCommand::Up] = true;
	buttonCanBeHeld[ControllerCommand::Down] = true;
	buttonCanBeHeld[ControllerCommand::Shield] = true;
	buttonCanBeHeld[ControllerCommand::Pause] = true;
}

GameController::~GameController()
{
}

/*When an input is detected, a command is raised to this function*/
void GameController::handleCommand(ControllerCommand command){
    /*Apply action on the menu dependant on the command*/
	if (player != NULL) {
		switch (command)
		{
		case ControllerCommand::Up:
		{
			//menu->inputUp();
			break;
		}
		case ControllerCommand::Down:
		{
			//menu->inputDown();
			break;
		}
		case ControllerCommand::Left:
		{
			//menu->inputLeft();
			break;
		}
		case ControllerCommand::Right:
		{
			//menu->inputRight();
			break;
		}
		case ControllerCommand::Shoot:
		{
			//menu->inputSelect();
			break;
		}
		case ControllerCommand::ShootAlt:
		{
			//menu->inputBack();
			break;
		}
		case ControllerCommand::Shield:
		{
			break;
		}
		case ControllerCommand::Pause:
		{
			//menu->inputSelect();
			break;
		}
		case ControllerCommand::Cheat:
		{
			//board->Cheat();
			break;
		}
		case ControllerCommand::NoInput:
		default: break;
		}
	}
	
}
  
void GameController::handleJoystickAxis(sf::Joystick::Axis axis) {
	//config->get
}

void GameController::handleMouseAxis() {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (mode == ControlMode::Keyboard) {
		player->setCursorOrientation(mousePos.x, mousePos.y);
	}
}
void GameController::setPlayer(Player* e){
        player = e;
}
