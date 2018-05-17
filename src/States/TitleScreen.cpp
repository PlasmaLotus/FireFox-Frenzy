#include "TitleScreen.h"
#include "../Main.h"
#include "StateManager.h"

TitleScreen::TitleScreen(sf::RenderWindow * w):
	MenuState(w, new MainMenu()){
	_idleTicks = 0;
	
}

void TitleScreen::tick(int dt, bool render) {
	bool input = false;
	if (p1Controller->handleInput()) {
		input = true;
	}
	
	if (p2Controller->handleInput()) {
		input = true;
	}
	
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
	if (!input) {
		_idleTicks += dt;
	}

}

TitleScreen::~TitleScreen(){
	delete menu;
	delete renderer;
	/*
	delete p1Controller;
	delete p2Controller;
	*/
}
