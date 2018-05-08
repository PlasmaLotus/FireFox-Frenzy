/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "ControllerConfig.h"
#include <ostream>
#include <fstream>
#include <iostream>
#include <string>

/*Contains all the commands that do stuff*/
ControllerConfig::ControllerConfig() :
	joystickNumber(0),
	joystickDeadZone(5.f),
	joystickMaxZone(70.f),
	controlMode(ControlMode::Keyboard){
	loadDefaultConfig();
}

ControllerConfig::ControllerConfig(std::string iniPath) :
	joystickNumber(0),
	joystickDeadZone(5.f),
	joystickMaxZone(70.f),
	controlMode(ControlMode::Keyboard){
	loadConfig(iniPath);
}

ControllerConfig::~ControllerConfig(){
	buttonMap.clear();
	keyMap.clear();
	axisMap.clear();
}

bool ControllerConfig::loadConfig(std::string iniPath){
	std::ifstream file;
	std::string line;
	file.open(iniPath);
	bool success = true;
	if (file.is_open()) {
		while (std::getline(file, line))
		{
			printf("%s\n",line);
			if (line.find("Mode") != std::string::npos) {
				if( line.find("Joystick") != std::string::npos) {
					controlMode = ControlMode::Joystick;
				}
				else
					controlMode = ControlMode::Keyboard;
			}
			else if (line.find("Joystick Number") != std::string::npos) {
				int jn = std::stoi(line.substr(std::strlen("Joystick Number"), 2));
				joystickNumber = jn;
			}
			else if(line.find("Command") != std::string::npos){
				std::string s = line.substr(std::strlen("Command"), 2);
				int commandNb = std::stoi(s);
				int assignNb;
				if (line.find("JButton") != std::string::npos) {
					std::string s2 = line.substr(line.find("JButton")+ std::strlen("JButton"), 2);
					assignNb = std::stoi(s2);
					buttonMap[assignNb] = static_cast<ControllerCommand>(commandNb);
				}
				else if (line.find("Axis") != std::string::npos) {
					std::string s2 = line.substr(line.find("Axis")+ std::strlen("Axis"), 2);
					assignNb = std::stoi(s2);
					bool positif = true;
					if (line.find("-") != std::string::npos) {
						positif = false;
					}
					AxisHandler handler;
					try {
						AxisHandler handler = axisMap.at(static_cast<sf::Joystick::Axis>(assignNb));
					}
					catch (const std::out_of_range& oor) {
						handler.positif = NoInput;
						handler.negatif = NoInput;
					}

					if (positif) {
						handler.positif = static_cast<ControllerCommand>(commandNb);
					}
					else {
						handler.negatif = static_cast<ControllerCommand>(commandNb);
					}
					axisMap[static_cast<sf::Joystick::Axis>(assignNb)] = handler;

				}
				else if (line.find("KeyboardKey") != std::string::npos) {
					std::string s2 = line.substr(line.find("KeyboardKey")+ std::strlen("KeyboardKey"), 2);
					assignNb = std::stoi(s2);
					keyMap[static_cast<sf::Keyboard::Key>(assignNb)] = static_cast<ControllerCommand>(commandNb);
				}
			}
		}
		file.close();
	}
	else {
		printf("Loading Default Config\n");
		loadDefaultConfig();
		success = false;
	}
	return success;
}

void ControllerConfig::loadDefaultConfig() {
	/*
	Pov XY = DPAD
	X Y = Left Analog
	R U = Right Analog
	Z: - = Right bumper, += Left bumper
	*/
	buttonMap.clear();
	keyMap.clear();
	axisMap.clear();
	setJoystickNumber(0);
	/*Defaultkeys*/
	keyMap[sf::Keyboard::Key::Up] = ControllerCommand::CursorUp;
	keyMap[sf::Keyboard::Key::Down] = ControllerCommand::CursorDown;
	keyMap[sf::Keyboard::Key::Left] = ControllerCommand::CursorLeft;
	keyMap[sf::Keyboard::Key::Right] = ControllerCommand::CursorRight;
	keyMap[sf::Keyboard::Key::W] = ControllerCommand::Up;
	keyMap[sf::Keyboard::Key::S] = ControllerCommand::Down;
	keyMap[sf::Keyboard::Key::A] = ControllerCommand::Left;
	keyMap[sf::Keyboard::Key::D] = ControllerCommand::Right;
	keyMap[sf::Keyboard::Key::Return] = ControllerCommand::Pause;
	keyMap[sf::Keyboard::Key::F] = ControllerCommand::Shoot;
	keyMap[sf::Keyboard::Key::R] = ControllerCommand::Dash;
	keyMap[sf::Keyboard::Key::F4] = ControllerCommand::Cheat;
	keyMap[sf::Keyboard::Key::E] = ControllerCommand::Shield;
	keyMap[sf::Keyboard::Key::BackSpace] = ControllerCommand::SwitchControlMode;

	buttonMap[0] = ControllerCommand::Shoot;
	buttonMap[1] = ControllerCommand::ShootAlt;
	buttonMap[2] = ControllerCommand::Dash;
	buttonMap[4] = ControllerCommand::Shield;//bumper //ForceRaise 
	buttonMap[5] = ControllerCommand::Shield;//bumper
	buttonMap[6] = ControllerCommand::Cheat;
	buttonMap[7] = ControllerCommand::Pause;

	//axisMap.insert(std::pair<sf::Joystick::Axis, AxisHandler>(sf::Joystick::Axis::PovY, { ControllerCommand::Up, ControllerCommand::Down}));
	axisMap[sf::Joystick::Axis::PovY] = { ControllerCommand::Down, ControllerCommand::Up };
	axisMap[sf::Joystick::Axis::PovX] = { ControllerCommand::Right, ControllerCommand::Left };
	axisMap[sf::Joystick::Axis::R] = { ControllerCommand::CursorUp, ControllerCommand::CursorDown };
	axisMap[sf::Joystick::Axis::U] = { ControllerCommand::CursorRight, ControllerCommand::CursorLeft };
	axisMap[sf::Joystick::Axis::Y] = { ControllerCommand::Up, ControllerCommand::Down };
	axisMap[sf::Joystick::Axis::X] = { ControllerCommand::Right, ControllerCommand::Left };
	axisMap[sf::Joystick::Axis::Z] = { ControllerCommand::Dash, ControllerCommand::Shoot };
	axisMap[sf::Joystick::Axis::V] = { ControllerCommand::Dash, ControllerCommand::Shield };
	//ControllerCommand::D
	//sf::Keyboard::Key::shi
}

bool ControllerConfig::saveConfig(){
	return saveConfig("esketit.test");
}

bool ControllerConfig::saveConfig(std::string iniPath){
	std::ofstream file;
	file.open(iniPath);
	if (controlMode == ControlMode::Joystick) {
		file << "Joystick Mode " << "\n";
	}
	else if (controlMode == ControlMode::Keyboard) {
		file << "Keyboard Mode " << "\n";
	}
	file << "Joystick Number" << joystickNumber << "\n";
	file << "\n";
	//Writing all joystick button maps 
	for (std::map<int, ControllerCommand>::iterator it = buttonMap.begin(); it != buttonMap.end(); ++it) {
		file << "Command" << it->second << " : " << "JButton" << it->first << "\n";
	}
	file << "\n";
	//Writing all Joystick Axis Bindings
	for (std::map<sf::Joystick::Axis, AxisHandler>::iterator it = axisMap.begin(); it != axisMap.end(); ++it) {
		file << "Command" << it->second.positif << " : " << "Axis" << it->first << " +" << "\n";
		file << "Command" << it->second.negatif << " : " << "Axis" << it->first << " -" << "\n";
	}
	file << "\n";
	//Writing all keyboard key bindings
	for (std::map<sf::Keyboard::Key, ControllerCommand>::iterator it = keyMap.begin(); it != keyMap.end(); ++it) {
		file << "Command" << it->second << " : " << "KeyboardKey" << it->first << "\n";
	}
	file.close();
	return true;
}

/*Havent tested Set Key yet*/
void ControllerConfig::setKey(ControllerCommand key, sf::Keyboard::Key value){
	keyMap.at(value) = key;
}
void ControllerConfig::setKey(ControllerCommand key, float value){
	//AxisHandler ah = axisMap.at(key);// = key;
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
			//if (value >= joystickMaxZone || value *-1 >= joystickMaxZone)//Higher than the treashhold to register max hold
			if (value > 0.f)//positif
			{
				command = axisMap.at(axis).positif;
			}
			else
			{
				command = axisMap.at(axis).negatif;
			}
		}
		catch (const std::out_of_range& oor) {
			command =  ControllerCommand::NoInput;
		}
	}
	return command;
}

ControllerCommand ControllerConfig::getCommand(unsigned int button)
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
		if (it->second.negatif == c || it->second.positif == c) {
			vec.push_back(it->first);
		}
	}
	return vec;
}

AxisHandler ControllerConfig::getAxisHandlerFromAxis(sf::Joystick::Axis axis) {
	try {
		AxisHandler ah = axisMap.at(axis);
		return AxisHandler(ah);
	}
	catch (const std::out_of_range& oor) {
		return AxisHandler{ NoInput, NoInput };
	}
}
