#include "OptionMenuState.h"
#include "../Main.h"
#include "StateManager.h"

OptionMenuState::OptionMenuState(sf::RenderWindow *w):
	MenuState(w, new Menu())
{
}

void OptionMenuState::tick() {
	//gotoxy(0, 5);
	printf("OPtion Menu State Tick \n");
	p1Controller->handleInput();
	p1Controller->updateConfig();
	renderer->render();
	menu->tick();

}

void OptionMenuState::goBack() {
	StateManager::getInstance().switchToState(new TitleScreen(StateManager::getInstance().getWindow()));
}
OptionMenuState::~OptionMenuState()
{
}
