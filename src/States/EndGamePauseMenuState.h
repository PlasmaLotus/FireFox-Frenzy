#ifndef __EndGamePauseMenuState__
#define __EndGamePauseMenuState__
#include "../States/MenuState.h"

class GameState;
class EndGamePauseMenuState : public MenuState {
public:
	EndGamePauseMenuState();
	EndGamePauseMenuState(GameState* gs, sf::RenderWindow * w);
	EndGamePauseMenuState(sf::RenderWindow *w);
	virtual void tick(int dt, bool render = true);
	virtual ~EndGamePauseMenuState();
	Menu* p2Menu;
};

#endif // PauseMenuState