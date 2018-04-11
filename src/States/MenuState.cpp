#include "MenuState.h"
#include "../Main.h"
#include "StateManager.h"

MenuState::MenuState():
MenuState(nullptr, nullptr){
}

MenuState::MenuState(sf::RenderWindow * w, Menu * m):
window(w),
menu(m)
{
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new MenuController(p1KeyConfig, menu);
	p2KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p2Controller = new MenuController(p2KeyConfig, menu);
	renderer = new MenuRenderer(window, menu);
}

MenuState::MenuState(sf::RenderWindow * w):
	MenuState(w, nullptr){
}

MenuState::MenuState(Menu * m) :
	MenuState(nullptr, m){
}

void MenuState::tick(int dt, bool render){
	p1Controller->handleInput();
	p1Controller->updateConfig();
	renderer->render();
	menu->tick();
}

MenuState::~MenuState()
{
	delete p1KeyConfig;
	delete p1Controller;
}
