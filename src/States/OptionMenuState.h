#pragma once
#ifndef OptionMenuState_H_
#define OptionMenuState_H_
#include <SFML\Graphics.hpp>
#include "MenuState.h"
class OptionMenuState : public MenuState
{
public:
	OptionMenuState(sf::RenderWindow *w);
	void tick();
	void goBack();
	~OptionMenuState();
	//Menu _currentMenu;
};

#endif