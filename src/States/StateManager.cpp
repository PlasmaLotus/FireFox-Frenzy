#include "StateManager.h"



StateManager::StateManager():
	_currentState(NULL),
	_newState(NULL),
	_switchState(false),
	_running(true)
{
	_id = 0;
	//p1Config = new ControllerConfig();
	//p2Config = new ControllerConfig();
	//p2Config->loadConfig("p2.config");
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TACD");
	//window.create(sf::VideoMode(240, 160), "PlasmaFlux");
	_currentState = new TitleScreen(&window);
	//renderer = new GameRenderer(w, currentState->getGame());

}

int StateManager::getWindowWidth()
{
	//window.getSize().x;
	return StateManager::getInstance().window.getSize().x;
}

int StateManager::getWindowHeight()
{
	return StateManager::getInstance().window.getSize().y;
}

StateManager::~StateManager()
{
	delete _newState;
	delete _currentState;
}

StateManager& StateManager::getInstance() {
	static StateManager instance;
	return instance;
}

void StateManager::switchToState(State* state) {
	_newState = state;
	_switchState = true;
}

void StateManager::goBack() {

	_currentState->goBack();
}

void StateManager::quit() {
	_running = false;
}

sf::RenderWindow *StateManager::getWindow() {
	return &window;
}

void StateManager::run()
{

	int frame = 0, milisecond = 0, second = 0, minute = 0;
	double MS_PER_FRAME = (1000.0) / FPS;//1000 ms per seconds
										 //int MS_PER_FRAME = 16;//miliseconds per frame
										 //clock_t FPS = 60;
	//sf::Clock currentTime;
	elapsedTime = currentTime.restart();
	window.setFramerateLimit(FPS);//framerate

	while (window.isOpen() && _running)
		{
			/*Manage Time Beta*/
			if (frame == 32767) {
				frame = 0;
			}
			else {
				frame++;
				milisecond++;

				if (milisecond >= 60)
				{
					second++;
					milisecond = 0;
				}

				if (second >= 60)
				{
					minute++;
					second = 0;
				}
			}
			if (frame % 1000 == 0) {
				system("cls");
			}
			/*~Manage Time Beta*/
			//current = clock();
			//elapsed = current - lastTime;
			currentTime.restart();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					_running = false;
				}
			}

			elapsedTime = currentTime.getElapsedTime();
			_currentState->tick();
			//elapsedTime.asMilliseconds()

			{
				gotoxy(0, 0);
				printf("Framerate: %3.5f \n ", elapsedTime.asMicroseconds() / 1000.f);
				printf("%d:%d  Frame: %d ", minute, second, frame);
				printf("NB Frames: %3.8f     Temps: %d    Clocks per Sec: %3.2f\n",
					(float)elapsedTime.asMilliseconds() * 60, elapsedTime.asMilliseconds(), (float)CLOCKS_PER_SEC);
				
				//gotoxy(0, 0);
			}

			if (_switchState) {
				delete _currentState;
				_currentState = _newState;
				_switchState = false;
				_newState = nullptr;
			}
		}

	return;
}

int32_t StateManager::getElapsedTime() {
	int i = std::nearbyint(1000.0 / FPS);
	printf("DT -- %d - %d    \n", 1000 / FPS, elapsedTime.asMicroseconds());
	//long
	//elapsedTime.as
	//return elapsedTime.asMilliseconds();
	return std::nearbyint( 1000.0 / FPS);
}

int StateManager::getUniqueID() {
	return _id++;
}

ControllerConfig *StateManager::getControllerConfig(int playerNumber)
{
	if (playerNumber == 1) {
		return &p1Config;
	}
	else {
		return &p2Config;
	}

}

std::string StateManager::getControllerConfigPath(int playerNumber)
{
	switch (playerNumber) {
	case 1: {
		return "p1Controls.ctl";
		break;
	}
	case 2:
	default: {
		return "p2Controls.ctl";
		break;
	}

	}

}