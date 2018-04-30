#include "PauseMenuState.h"
#include "../Menu/PauseMenu.h"
#include "../States/StateManager.h"

PauseMenuState::PauseMenuState():
	PauseMenuState(nullptr, nullptr){
}

PauseMenuState::PauseMenuState(sf::RenderWindow *w) :
	PauseMenuState(w, nullptr) {
}

PauseMenuState::PauseMenuState(Menu * m) :
	PauseMenuState(nullptr, m) {
}
PauseMenuState::PauseMenuState(sf::RenderWindow * w, Menu * m) :
	//MenuState()
	MenuState(w, new PauseMenu())
{
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new MenuController(p1KeyConfig, menu);
	p2KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p2Controller = new MenuController(p2KeyConfig, menu);
	renderer = new MenuRenderer(window, menu);
	//renderer = new PauseMenuRenderer(window, menu);

	p2Menu = new PauseMenu();
}


PauseMenuState::~PauseMenuState() {
	delete menu;
	delete p2Menu;
	delete renderer;
}

void PauseMenuState::tick(int dt, bool render) {
	p1Controller->handleInput();
	p2Controller->handleInput();
	/*
	p1Controller->updateConfig();
	p2Controller->updateConfig();
	*/
	renderer->render();
	menu->tick();
}