#ifndef __PauseMenu__
#define __PauseMenu__
#include "../States/MenuState.h"

class PauseMenuState : public MenuState {
public:
	//PauseMenuState(sf::RenderWindow *w);
	PauseMenuState();
	PauseMenuState(sf::RenderWindow * w, Menu *m);
	PauseMenuState(sf::RenderWindow *w);
	PauseMenuState(Menu * m);
	virtual void tick(int dt, bool render = true);
	virtual ~PauseMenuState();
	Menu* p2Menu;
};

#endif // PauseMenuState