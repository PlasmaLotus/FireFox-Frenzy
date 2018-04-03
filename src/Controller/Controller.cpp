/*
Created by PlasmaLotus
Updated August 06, 2017
*/
#include "Controller.h"

/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute on the Board and Game*/
Controller::Controller(ControllerConfig* c) :
mode(ControlMode::Keyboard),
_nextMode(ControlMode::Keyboard),
_swapConfig(false),
config(c)
{
	if (config != NULL) {
		//config->loadConfig("controllerConfig.ini");
	}
}

Controller::~Controller(){
}

void Controller::updateConfig(){

	if (!sf::Joystick::isConnected(config->getJoystickNumber()))
	{
		config->setJoystickNumber(0);
		joystickConnected = true;
	}
	else {
		joystickConnected = false;
	}
}

void Controller::setControlMode(ControlMode cm) {
	mode = cm;
}
 
/*Checks all the inputs related to the keyboard*/
void Controller::handleInputKeyboard() {
	/*Check Every key on the keyboard for a conrresponding key*/
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
		if (sf::Keyboard::isKeyPressed(key))
		{
			handleCommand(config->getCommand(key));
		}
	}
}

/*Check all imput related to a joystick and calls the command handler*/
void Controller::handleInputJoystick() {
	unsigned int js = config->getJoystickNumber();
	/*Check Buttons*/
	for (unsigned int i = 0; i < sf::Joystick::getButtonCount(js); i++)
	{
		if (sf::Joystick::isButtonPressed(js, i)) {
			if (mode == ControlMode::Joystick) {
				handleCommand(config->getCommand(i));
			}
			else {
				swapToControlMode(ControlMode::Joystick);
			}
		}
	}
	/*Check Axis*/
	for (int i = 0; i < sf::Joystick::AxisCount; i++)
	{
		sf::Joystick::Axis axis = static_cast<sf::Joystick::Axis>(i);
		if (sf::Joystick::hasAxis(js, axis))
		{
			if (mode == ControlMode::Joystick) {
				//handleCommand(config->getCommand(axis, sf::Joystick::getAxisPosition(js, axis)));
				handleJoystickAxis(axis);
			}
			else {
				swapToControlMode(ControlMode::Joystick);
			}
			
		}
	}
}

void Controller::viewDebugJoystick() {
	printf("DebugJoystickInputs\n");
	//if (mode == ControlMode::Joystick) {
		printf("\nDebug Joystick %d info\n", config->getJoystickNumber());
		printf("X Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::X));
		printf("Y Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::Y));
		printf("PovX Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::PovX));
		printf("PovY Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::PovY));
		printf("R Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::R));
		printf("U Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::U));
		printf("V Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::V));
		printf("Z Axis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::Z));
	//}
}

	/*Handles all the input of the mouse*/
void Controller::handleInputMouse() {
	for (int i = 0; i < sf::Mouse::ButtonCount; i++)
	{
		sf::Mouse::Button mouseButton = static_cast<sf::Mouse::Button>(i);
		if (sf::Mouse::isButtonPressed(mouseButton)) {
			if (mode == ControlMode::Keyboard){
				//handleCommand(config->getCommand(mouseButton));
			}
			else{
				swapToControlMode(ControlMode::Keyboard);
			}
		}
	}
	handleMouseAxis();
}

/*Main input check call -- Checks if any input is pressed and acts accordingly*/
bool Controller::handleInput() {
	bool input = false;
	if (config != NULL) {
		if (_swapConfig) {
			mode = _nextMode;
			_swapConfig = false;
		}
		handleInputKeyboard();
		handleInputMouse();
		handleMouseAxis();
		if (sf::Joystick::isConnected(config->getJoystickNumber())) {
			//mode = ControlMode::Joystick;
			handleInputJoystick();
		}
	}
	return true;
}

void Controller::handleCommand(ControllerCommand command) {
	/*Apply action dependant on the command*/
}
void Controller::handleJoystickAxis(sf::Joystick::Axis) {
	/*Apply action dependant on the Axis*/
}
void Controller::handleMouseAxis(){
	/*Apply action dependant on the MousePos*/
}
void Controller::swapToControlMode(ControlMode m)
{
	_nextMode = m;
	_swapConfig = true;
}
ControllerConfig* Controller::getConfig() {
	return config;
}

void Controller::__updateConfig() {
	if (mode == ControlMode::Keyboard) {
		if (sf::Joystick::isConnected(0))
		{
			mode = ControlMode::Joystick;
			config->setJoystickNumber(0);
		}
		else
		{
			mode = ControlMode::Keyboard;
		}
	}
	else if (mode == ControlMode::Joystick) {

		if (!sf::Joystick::isConnected(config->getJoystickNumber()))
		{
			mode = Keyboard;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			mode = Keyboard;
		}
	}
}