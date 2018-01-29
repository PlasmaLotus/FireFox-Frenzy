#pragma once
/*
Created by PlasmaLotus
Updated May 17, 2017
*/

#ifndef __StateManager__
#define __StateManager__

//#include "SFML\Graphics.hpp"
#include "State.h"
//#include "GameState.h"
#include "MenuState.h"
#include "TitleScreen.h"
//#include "OptionMenuState.h"
//#include "../Renderer/GameRenderer.h"
#include "../Main.h"

class StateManager {
public:
	~StateManager();
	static StateManager& getInstance();
	void switchToState(State* state);
	void goBack();
	void quit();
	sf::RenderWindow * getWindow();
	void run();
	int32_t getElapsedTime();
	//void play();
	static const int FPS = 60;
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
private:
	StateManager();
	bool _running;
	sf::RenderWindow window;
	State *_currentState;
	State *_newState;
	sf::Clock currentTime;
	sf::Time elapsedTime;
	bool _switchState;
	//GameRenderer *renderer;
	
};

#endif
