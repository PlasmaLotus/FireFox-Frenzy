#include "PauseMenuState.h"
#include "../Menu/PauseMenu.h"

PauseMenuState::PauseMenuState(sf::RenderWindow *w):
MenuState(w, new PauseMenu()){
	p2Menu = new PauseMenu();
	
};
PauseMenuState::~PauseMenuState() {
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