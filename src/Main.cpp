//#include "SFML\Graphics.hpp"
//#include <SFML/Graphics.hpp>
#include"States\StateManager.h"
#include "Main.h"
int main(int argc, char *argv[])
{
	StateManager& sm = StateManager::getInstance();
	sm.run();
	
	return 0;
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}