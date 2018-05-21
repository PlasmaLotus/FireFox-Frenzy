#include "OptionMenuState.h"
//#include "../Menu/OptionsMenu.h"
#include "../Main.h"
#include "StateManager.h"

OptionMenuState::OptionMenuState(sf::RenderWindow *w):
	MenuState(w, new OptionsMenu())
{
}

void OptionMenuState::tick(int dt, bool render) {
	printf("OPtion Menu State Tick \n");
	p1Controller->handleInput();
	p2Controller->handleInput();
	p1Controller->updateConfig();
	p2Controller->updateConfig();
	renderer->render();
	menu->tick(dt);
	printf("NB SELECTIONS: %i\n", menu->getItems().size());
	printf("CurrentSelection: %d\n", menu->getSelection());
	printf("-- Menu Options --\n");
	for (unsigned i = 0; i < menu->getItems().size(); ++i) {
		if (i == menu->getSelection()) {
			printf(">>>");
		}
		printf("%s   \n", menu->getItems().at(i).getOptionString().c_str());
	}
}

/*
void OptionMenuState::goBack() {
	StateManager::getInstance().switchToState(new TitleScreen(StateManager::getInstance().getWindow()));
}
*/
OptionMenuState::~OptionMenuState(){
	delete menu;
	delete renderer;
	/*
	delete p1Controller;
	delete p2Controller;
	*/
}
