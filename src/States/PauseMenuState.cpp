#include "PauseMenuState.h"
#include "../Menu/PauseMenu.h"
#include "../States/StateManager.h"
#include "../States/GameState.h"
#include "../Renderer/PauseMenuRenderer.h"

PauseMenuState::PauseMenuState():
	PauseMenuState(nullptr, nullptr){
}
PauseMenuState::PauseMenuState(sf::RenderWindow * w) :
	PauseMenuState(nullptr, w){
}

PauseMenuState::PauseMenuState(GameState* gs, sf::RenderWindow * w) :
	//MenuState()
	MenuState(w, new PauseMenu(gs))
{
	/*
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new MenuController(p1KeyConfig, menu);
	p2KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(2));
	p2Controller = new MenuController(p2KeyConfig, menu);
	//renderer = new MenuRenderer(window, menu);
	*/
	renderer = new PauseMenuRenderer(window, menu);

	p2Menu = new PauseMenu();
}


PauseMenuState::~PauseMenuState() {
	delete menu;
	delete p2Menu;
	delete renderer;
	/*
	if (p1KeyConfig != nullptr) {
		delete p1KeyConfig;
	}
	if (p2KeyConfig != nullptr) {
		delete p2KeyConfig;
	}
	if (p1Controller != nullptr) {
		delete p1Controller;
	}
	if (p2Controller != nullptr) {
		delete p2Controller;
	}
	*/
}

void PauseMenuState::tick(int dt, bool render) {
	renderer->render();
	menu->tick(dt);
	p1Controller->handleInput();
	p2Controller->handleInput();
}

