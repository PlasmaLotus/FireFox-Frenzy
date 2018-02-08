/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "ControllerConfig.h"
#include <ostream>
#include <fstream>

/*Contains all the commands that do stuff*/
ControllerConfig::ControllerConfig() :
	joystickNumber(0),
	joystickDeadZone(15.f),
	joystickMaxZone(60.f),
	controlMode(ControlMode::Keyboard)
{

	/*
	Pov XY = DPAD
	X Y = Left Analog
	R U = Right Analog
	Z: - = Right bumper, += Left bumper
	*/


	/*Defaultkeys*/
	keyMap[sf::Keyboard::Key::Up] = ControllerCommand::Up;
	keyMap[sf::Keyboard::Key::Down] = ControllerCommand::Down;
	keyMap[sf::Keyboard::Key::Left] = ControllerCommand::Left;
	keyMap[sf::Keyboard::Key::Right] = ControllerCommand::Right;
	keyMap[sf::Keyboard::Key::Return] = ControllerCommand::Pause;
	keyMap[sf::Keyboard::Key::X] = ControllerCommand::Shoot;
	keyMap[sf::Keyboard::Key::Z] = ControllerCommand::ShootAlt;
	keyMap[sf::Keyboard::Key::F4] = ControllerCommand::Cheat;
	keyMap[sf::Keyboard::Key::A] = ControllerCommand::Shield;
	keyMap[sf::Keyboard::Key::BackSpace] = ControllerCommand::SwitchControlMode;

	buttonMap[0] = ControllerCommand::Shoot;
	buttonMap[1] = ControllerCommand::ShootAlt;
	buttonMap[2] = ControllerCommand::Shoot;
	buttonMap[4] = ControllerCommand::Shield;//bumper //ForceRaise 
	buttonMap[5] = ControllerCommand::Shield;//bumper
	buttonMap[6] = ControllerCommand::Cheat;
	buttonMap[7] = ControllerCommand::Pause;

	//axisMap.insert(std::pair<sf::Joystick::Axis, AxisHandler>(sf::Joystick::Axis::PovY, { ControllerCommand::Up, ControllerCommand::Down}));
	axisMap[sf::Joystick::Axis::PovY] = { ControllerCommand::Up, ControllerCommand::Up, ControllerCommand::Down , ControllerCommand::Down };
	axisMap[sf::Joystick::Axis::PovX] = { ControllerCommand::Right, ControllerCommand::Right, ControllerCommand::Left, ControllerCommand::Left };
	axisMap[sf::Joystick::Axis::Y] = { ControllerCommand::NoInput, ControllerCommand::Down, ControllerCommand::NoInput, ControllerCommand::Up };
	axisMap[sf::Joystick::Axis::X] = { ControllerCommand::NoInput, ControllerCommand::Right, ControllerCommand::NoInput, ControllerCommand::Left };
	//keyMap.insert(std::pair<sf::Keyboard::Key, ControllerCommand>(sf::Keyboard::Key::Up, ControllerCommand::Up));
}

ControllerConfig::~ControllerConfig()
{
	buttonMap.clear();
	keyMap.clear();
	axisMap.clear();
}

bool ControllerConfig::loadConfig(std::string iniPath){
	printf("Loading Config");
	if ((float)joystickNumber == joystickNumber)
	{
		return true;
	}
	return false;
}

bool ControllerConfig::saveConfig()
{

	std::ofstream file;
	file.open("esketit.test");
	//file << "Writing this to a file.\n";
	if (controlMode == ControlMode::Joystick) {
		file << "Joystick Mode " << "\n";
	}
	else if (controlMode == ControlMode::Keyboard) {
		file << "Keyboard Mode " << "\n";
	}
	file << "Joystick Number: " << joystickNumber << "\n";
	for (std::map<int, ControllerCommand>::iterator it = buttonMap.begin(); it != buttonMap.end(); ++it) {
		//Enum ^ ControllerCommand c = ;
		file << "Command" << it->second << " : " << "Button" << it->first << "\n";
	}

	file.close();
	return false;
}

/*Havent tested Set Key yet*/
void ControllerConfig::setKey(ControllerCommand key, sf::Keyboard::Key value){
	keyMap.at(value) = key;
}
void ControllerConfig::setKey(ControllerCommand key, float value){
	//axisMap.at(value) = key;
}
void ControllerConfig::setKey(ControllerCommand key, int value){
	buttonMap.at(value) = key;
}

ControllerCommand ControllerConfig::getCommand(sf::Keyboard::Key key)
{
	ControllerCommand command = ControllerCommand::NoInput;
	try {
		command = (keyMap.at(key));    //get the command associated to the key
	}
	catch (const std::out_of_range& oor) {
		command = ControllerCommand::NoInput;
	}
	return command;
}

ControllerCommand ControllerConfig::getCommand(sf::Joystick::Axis axis, float value)
{
	ControllerCommand command = ControllerCommand::NoInput;
	if (value > joystickDeadZone || value *-1 > joystickDeadZone)//if the value is over the dead zone
	{
		try {
			if (value >= joystickMaxZone || value *-1 >= joystickMaxZone)//Higher than the treashhold to register max hold
			{
				if (value > 0.f)//positif
				{
					command = axisMap.at(axis).positifMax;
				}
				else
				{
					command = axisMap.at(axis).negatifMax;
				}
			}
			else
			{
				if (value > 0.f)//positif
				{
					command = axisMap.at(axis).positif;
				}
				else
				{
					command = axisMap.at(axis).negatif;
				}
			}
		}
		catch (const std::out_of_range& oor) {
			command =  ControllerCommand::NoInput;
		}
	}
	return command;

}

ControllerCommand ControllerConfig::getCommand(int button)
{
	ControllerCommand command = ControllerCommand::NoInput;
	if (button < sf::Joystick::getButtonCount(joystickNumber))
	{
		try {
			command = (buttonMap.at(button));//get the command associated to the button
		}
		catch (const std::out_of_range& oor) {
			command = ControllerCommand::NoInput;
		}
	}
	return command;
}

int ControllerConfig::getJoystickNumber(void)
{
	return joystickNumber;
}

void ControllerConfig::setJoystickNumber(int number) {
	joystickNumber = number;
}

void ControllerConfig::getKeys() {
	std::vector<sf::Keyboard::Key> vec;
	for (std::map<sf::Keyboard::Key, ControllerCommand>::iterator it = keyMap.begin(); it != keyMap.end(); ++it) {
		vec.push_back(it->first);
		//cout << it->first << "\n";
	}
}

std::vector<sf::Keyboard::Key> ControllerConfig::getKeyboardKeys(ControllerCommand c) {
	std::vector<sf::Keyboard::Key> vec;
	for (std::map<sf::Keyboard::Key, ControllerCommand>::iterator it = keyMap.begin(); it != keyMap.end(); ++it) {
		if (it->second == c) {
			vec.push_back(it->first);
		}
	}
	return vec;
}

std::vector<int> ControllerConfig::getButtonKeys(ControllerCommand c) {
	std::vector<int> vec;
	for (std::map<int, ControllerCommand>::iterator it = buttonMap.begin(); it != buttonMap.end(); ++it) {
		if (it->second == c) {
			vec.push_back(it->first);
		}
	}
	return vec;
}

std::vector<sf::Joystick::Axis> ControllerConfig::getAxisKeys(ControllerCommand c) {
	std::vector<sf::Joystick::Axis> vec;
	for (std::map<sf::Joystick::Axis, AxisHandler>::iterator it = axisMap.begin(); it != axisMap.end(); ++it) {
		/*
		if (it->second == c) {
			vec.push_back(it->first);
		}
		*/
	}
	return vec;
}