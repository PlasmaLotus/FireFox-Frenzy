#include "StateManager.h"



StateManager::StateManager():
	_currentState(NULL),
	_newState(NULL),
	_switchState(false)
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TACD");
	_currentState = new TitleScreen(&window);
	eventManager.setAudioEventManager(&audioEventManager);
}

int StateManager::getWindowWidth()
{
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
	elapsedTime = currentTime.restart();
	window.setFramerateLimit(FPS);//framerate

	while (window.isOpen() && _running)
		{
			/*Manage Time Beta*/
			if (frame == 32767) {
				frame = 0;
			}

			if (frame % 1000 == 0) {
				system("cls");
			}

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
			_run();

			{
				gotoxy(0, 0);
				printf("%d:%d  Frame: %d ", minute, second, frame);
				printf("NB Frames: %3.8f     Temps: %d    Clocks per Sec: %3.2f\n",
					(float)elapsedTime.asMilliseconds() * 60, elapsedTime.asMilliseconds(), (float)CLOCKS_PER_SEC);
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

void StateManager::_run() {
	eventManager.handleEvents(getElapsedTime());
	audioEventManager.handleEvents(getElapsedTime());
	_currentState->tick();
}
int32_t StateManager::getElapsedTime() {
	int i = std::nearbyint(1000.0 / FPS);
	printf("DT -- %d - %d    \n", 1000 / FPS, elapsedTime.asMicroseconds());
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