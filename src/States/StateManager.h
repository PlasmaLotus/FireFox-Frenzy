#pragma once
/*
Created by PlasmaLotus
Updated May 17, 2017
*/
#ifndef __StateManager__
#define __StateManager__

#include <stdint.h>
#include <string.h>
#include <stack>
#include "State.h"
#include "MenuState.h"
#include "TitleScreen.h"
#include "../Controller/ControllerConfig.h"
#include "../Main.h"
#include "../Event/EventManager.h"
#include "../Event/AudioEventManager.h"

class StateManager {
public:
	~StateManager();
	static StateManager& getInstance();
	void switchToState(State* state);
	void goBack();
	void quit();
	sf::RenderWindow * getWindow();
	void run();
	int64_t getElapsedTime();
	int64_t getRenderElapsedTime();
	int getUniqueID();
	static const int FPS = 144;
	static const int renderFPS = 60;
	int SCREEN_WIDTH = 1080;
	int SCREEN_HEIGHT = 720;
	ControllerConfig *getControllerConfig(int playerNumber);
	static std::string getControllerConfigPath(int playerNumber);
	static int getWindowWidth();
	static int getWindowHeight();
	void _run();
	EventManager eventManager;
	AudioEventManager audioEventManager;
	std::string getCurrentGameTimer();
	void resetGameTimer();
protected:
	StateManager();
	int _id{ 0 };
	bool _running{ true };
	sf::RenderWindow window;
	State *_currentState;
	State *_newState;
	std::stack<State*> _states;
	sf::Clock currentTime;
	sf::Time elapsedTime;
	sf::Time renderElapsedTime;
	bool _switchState;
	ControllerConfig p1Config;
	ControllerConfig p2Config;
	bool _renderFrame{ true };
	sf::Clock gameTimer;
};
#endif 
