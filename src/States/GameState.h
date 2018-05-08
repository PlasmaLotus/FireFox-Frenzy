 /*
Created by PlasmaLotus
Updated May 17, 2017
*/
#ifndef __GameState__
#define __GameState__

#include "State.h"
#include "../Game/GameLogic.h"
#include "../Renderer/GameRenderer.h"
#include "../Controller/GameController.h"
#include "../Event/EventManager.h"
#include "PauseMenuState.h"
class GameState : public State {
public:
	GameState(sf::RenderWindow *w);
	virtual ~GameState();
	virtual void tick(int dt, bool render = true);
	GameLogic *getGame();
	void pause();
	void reset();
	GameRenderer* getRenderer();
private:
	GameLogic *game;
	GameRenderer *renderer;
	sf::RenderWindow *window;
	GameController *p1Controller;
	GameController *p2Controller;
	ControllerConfig* p1KeyConfig;
	ControllerConfig* p2KeyConfig;
	PauseMenuState* pauseMenuState;
};
#endif
