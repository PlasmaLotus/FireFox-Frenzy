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
			if (frame % 10000) {
				//system("cls");
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
				printf("%d:%d  Frame: %d\n", minute, second, frame);
				printf("NB Frames: %3.2f     \nTemps: %d           \nClocks per Sec: %3.2f\n",
					(float)elapsedTime.asMilliseconds() * 60, elapsedTime, (float)CLOCKS_PER_SEC);
				
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
	printf("DT -- %3.9f\n", elapsedTime.asSeconds());
	//long
	//elapsedTime.as
	//return elapsedTime.asMilliseconds();
	return 1000 / FPS;
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
	if (playerNumber == 1) {
		return "p1Controls.ctl";
	}
	else {
		return "p2Controls.ctl";
	}

}