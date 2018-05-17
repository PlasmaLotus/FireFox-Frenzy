#include "EndGamePauseMenuState.h"
#include "../Menu/EndGamePauseMenu.h"
#include "../States/StateManager.h"
#include "../States/GameState.h"
#include "../Renderer/PauseMenuRenderer.h"

EndGamePauseMenuState::EndGamePauseMenuState():
	EndGamePauseMenuState(nullptr, nullptr){
}
EndGamePauseMenuState::EndGamePauseMenuState(sf::RenderWindow * w) :
	EndGamePauseMenuState(nullptr, w){
}

EndGamePauseMenuState::EndGamePauseMenuState(GameState* gs, sf::RenderWindow * w) :
	//MenuState()
	MenuState(w, new EndGamePauseMenu(gs))
{
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new MenuController(p1KeyConfig, menu);
	p2KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(2));
	p2Controller = new MenuController(p2KeyConfig, menu);
	//renderer = new MenuRenderer(window, menu);
	renderer = new PauseMenuRenderer(window, menu);

	p2Menu = new EndGamePauseMenu();
}


EndGamePauseMenuState::~EndGamePauseMenuState() {
	delete menu;
	delete p2Menu;
	delete renderer;
}

void EndGamePauseMenuState::tick(int dt, bool render) {
	renderer->render();
	menu->tick(dt);
	p1Controller->handleInput();
	p2Controller->handleInput();
}

