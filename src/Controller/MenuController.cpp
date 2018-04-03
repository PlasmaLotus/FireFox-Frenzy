/*
Created by PlasmaLotus
Updated May 13, 2017
*/
#include "MenuController.h"

/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute on the Board and Game*/
MenuController::MenuController(ControllerConfig* c, Menu* m) :
Controller(c),
menu(m){
}

MenuController::~MenuController(){
}

/*Act accordingly to the needed commands*/
void MenuController::handleCommand(ControllerCommand command){
    /*Apply action on the menu dependant on the command*/
	if (menu != NULL) {
		switch (command)
		{
		case ControllerCommand::Up:
		{
			menu->inputUp();
			break;
		}
		case ControllerCommand::Down:
		{
			menu->inputDown();
			break;
		}
		case ControllerCommand::Left:
		{
			menu->inputLeft();
			break;
		}
		case ControllerCommand::Right:
		{
			menu->inputRight();
			break;
		}
		case ControllerCommand::Shoot:
		{
			menu->inputSelect();
			break;
		}
		case ControllerCommand::ShootAlt:
		{
			menu->inputBack();
			break;
		}
		case ControllerCommand::Shield:
		{
			break;
		}
		case ControllerCommand::Pause:
		{
			menu->inputSelect();
			break;
		}
		case ControllerCommand::Cheat:
		{
			break;
		}
		case ControllerCommand::NoInput:
		default: break;
		}
	}
	
}

void MenuController::handleJoystickAxis(sf::Joystick::Axis axis) {
	AxisHandler handler = config->getAxisHandlerFromAxis(axis);
	float value = sf::Joystick::getAxisPosition(config->getJoystickNumber(), axis);
	ControllerCommand command;
	if (value > 0) {
		command = handler.positif;
	}
	else {
		command = handler.negatif;
	}
	switch (command) {
	case ControllerCommand::Up:
	{
		if (value >= config->joystickDeadZone || value <= -config->joystickDeadZone) {
			menu->inputUp();
		}
		break;
	}
	case ControllerCommand::Down:
	{
		if (value >= config->joystickDeadZone || value <= -config->joystickDeadZone) {
			menu->inputDown();
		}
		break;
	}

	case ControllerCommand::Left: {
		if (value >= config->joystickDeadZone || value <= -config->joystickDeadZone) {
			menu->inputLeft();
		}
		break;
	}
	case ControllerCommand::Right:
	{
		if (value >= config->joystickDeadZone || value <= -config->joystickDeadZone) {
			menu->inputRight();
		}
		break;
	}

	case ControllerCommand::CursorUp:
	case ControllerCommand::CursorDown:
	case ControllerCommand::CVertical:
	{
		break;
	}

	case ControllerCommand::CursorLeft:
	case ControllerCommand::CursorRight:
	case ControllerCommand::CHorizontal:
	{
		break;
	}
	case ControllerCommand::Shoot:
	case ControllerCommand::ShootAlt: {
		if (value >= config->joystickDeadZone || value <= -config->joystickDeadZone) {
			menu->inputSelect();
		}
		break;
	}
	case ControllerCommand::Dash: {
		if (value >= config->joystickDeadZone || value <= -config->joystickDeadZone) {
			menu->inputBack();
		}
		break;
	}
	case ControllerCommand::Shield: {
		if (value >= config->joystickDeadZone || value <= -config->joystickDeadZone) {
			menu->inputBack();
		}
		break;
	}
	default:
		break;
	}
}

void MenuController::handleMouseAxis() {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (mode == ControlMode::Keyboard) {
		//player->setCursorOrientation(mousePos.x, mousePos.y);
	}
}

void MenuController::setMenu(Menu* b){
        menu = b;
}
