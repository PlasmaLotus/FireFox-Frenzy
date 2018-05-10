#ifndef __PauseMenu__
#define __PauseMenu__
#include "../States/MenuState.h"

class GameState;
class PauseMenuState : public MenuState {
public:
	PauseMenuState();
	PauseMenuState(GameState* gs, sf::RenderWindow * w);
	PauseMenuState(sf::RenderWindow *w);
	virtual void tick(int dt, bool render = true);
	virtual ~PauseMenuState();
	Menu* p2Menu;
};

#endif // PauseMenuState