#include "MenuState.h"
#include "../Main.h"
#include "StateManager.h"

MenuState::MenuState()
{
	
}

MenuState::MenuState(sf::RenderWindow * w, Menu * m):
window(w),
menu(m)
{
	//currentMenu = new MainMenu(window);
	p1KeyConfig = new ControllerConfig();
	p1Controller = new MenuController(p1KeyConfig, menu);
	//p1Controller->config = StateManager::getInstance().getControllerConfig(1);
	//p1Controller = new MenuController(StateManager::getInstance().getControllerConfig(1), menu);
	renderer = new MenuRenderer(window, menu);
	//renderer = new Renderer(window);
}

MenuState::MenuState(sf::RenderWindow * w):
	window(w)
{
	//currentMenu = new MainMenu(window);
	menu = new Menu();
	//p1KeyConfig = new ControllerConfig();
	p1Controller = new MenuController(StateManager::getInstance().getControllerConfig(1), menu);
	renderer = new MenuRenderer(window, menu);
	//renderer = new Renderer(window);
}

void MenuState::tick()
{
	gotoxy(0, 5);
	printf("Menu State Tick \n");
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
