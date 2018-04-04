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
	//currentMenu = new MainMenu(window);
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new MenuController(p1KeyConfig, menu);
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new MenuController(p1KeyConfig, menu);
	renderer = new MenuRenderer(window, menu);
}

MenuState::MenuState(sf::RenderWindow * w):
	MenuState(w, nullptr){
}

MenuState::MenuState(Menu * m) :
	MenuState(nullptr, m){
}

void MenuState::tick()
{
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
