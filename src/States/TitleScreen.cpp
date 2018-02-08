#include "TitleScreen.h"
#include "../Main.h"

TitleScreen::TitleScreen(sf::RenderWindow * w):
	MenuState(w, new MainMenu())
{
	p1Controller->getConfig()->saveConfig();
}

void TitleScreen::tick() {
	gotoxy(0, 5);
	printf("Title Screen State Tick \n");
	p1Controller->handleInput();
	p1Controller->updateConfig();
	renderer->render();
	menu->tick();

	//printf("MenuItems\n");
	printf("NB SELECTIONS: %d\n", menu->items.size());
	printf("CurrentSelection: %d\n", menu->selection);
	for (unsigned i = 0; i < menu->items.size(); ++i) {
		if (i == menu->selection) {
			printf(">>>");
		}
		printf("%s\n", menu->items.at(i).getName());
	}


}


TitleScreen::~TitleScreen()
{
}
