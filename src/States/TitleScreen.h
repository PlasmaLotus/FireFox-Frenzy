#pragma once

#ifndef STATES_TITLESCREEN_H_
#define STATES_TITLESCREEN_H_

#include <SFML\Graphics.hpp>
#include "MenuState.h"
#include "../Menu/MainMenu.h"

class MenuState;

class TitleScreen : public MenuState
{
public:
	TitleScreen(sf::RenderWindow *w);
	void tick();
	~TitleScreen();
private:
	int _idleTicks;
};

#endif