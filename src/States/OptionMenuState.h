
#ifndef OptionMenuState_H_
#define OptionMenuState_H_

#include <SFML\Graphics.hpp>
#include "../Menu/OptionsMenu.h"
#include "MenuState.h"
class OptionMenuState : public MenuState
{
public:
	OptionMenuState(sf::RenderWindow *w);
	virtual void tick(int dt, bool render = true);
	//virtual void goBack();
	~OptionMenuState();
	//Menu _currentMenu;
};

#endif