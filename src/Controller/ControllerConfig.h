/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _ControllerConfig_H_
#define _ControllerConfig_H_

#include <string.h>
#include <map>
#include <vector>
#include <SFML/Window.hpp>


enum ControlMode { Keyboard, Joystick };
//#include "Controller.h"
//Down -, Left -
enum ControllerCommand { NoInput2, Up, Down, Left, Right, CursorUp, CursorDown, CursorLeft, CursorRight, PVertical, PHorizontal, CVertical, CHorizontal, Pause, Cheat, Shoot, ShootAlt, Shield, Dash, SwapWeapon, SwitchControlMode, NoInput, CommandMax = NoInput};
enum ControllerInputType{KeyboardKey, MouseButton, MouseAxis, JoystickButton, JoystickAxis};

struct AxisHandler {
	//sf::Joystick::Axis axis;
	ControllerCommand positif;
	
	ControllerCommand negatif;

};

class ControllerConfig{
public:
    ControllerConfig();
	ControllerConfig(std::string iniPath);
    ~ControllerConfig();
    bool loadConfig(std::string iniPath);
	void loadDefaultConfig();
	bool saveConfig(std::string iniPath);
	bool saveConfig();
    void setKey(ControllerCommand key, sf::Keyboard::Key value);
    void setKey(ControllerCommand key, float value);
    void setKey(ControllerCommand key, int value);
    ControllerCommand getCommand(sf::Keyboard::Key key);
    ControllerCommand getCommand(sf::Joystick::Axis axis, float value);
    ControllerCommand getCommand(int button);
	int getJoystickNumber(void);
	void setJoystickNumber(int number);
	void getKeys();
	std::vector<sf::Keyboard::Key> getKeyboardKeys(ControllerCommand c);
	std::vector<int> getButtonKeys(ControllerCommand c);
	std::vector<sf::Joystick::Axis> getAxisKeys(ControllerCommand c);
	AxisHandler getAxisHandlerFromAxis(sf::Joystick::Axis axis);
	ControllerCommand getAxisCommand(sf::Joystick::Axis axis);
    float joystickDeadZone;//Zone in witch no input should result;
    float joystickMaxZone;//Difference between slighlty held and Max held, if necessary
private:

	/*Cette structure de donnée me permet d'assigner une commande a chaque bouton, je suis ouvert au changements*/
	std::map<sf::Keyboard::Key, ControllerCommand> keyMap;
	std::map<int, ControllerCommand> buttonMap;
	std::map<sf::Joystick::Axis, AxisHandler> axisMap;
	std::map<int, ControllerCommand> mouseButtonMap;

	ControlMode controlMode;
    unsigned int joystickNumber;//the joystick in question 

};

#endif
