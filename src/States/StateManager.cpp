#include "StateManager.h"
#include "GameState.h"


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
	gameTimer.restart();
	elapsedTime = currentTime.restart();
	renderElapsedTime = currentTime.restart();
	window.setFramerateLimit(FPS);//framerate
	float renderElapsedTimeFloat{ 0.f };
	renderElapsedTimeFloat += currentTime.getElapsedTime().asMicroseconds();
	while (window.isOpen() && _running)
		{
			/*Manage Time Beta*/
			if (frame >= 32767) {
				frame = 0;
			}

			if (frame % 10000 == 0) {
				//system("cls");
			}
			_renderFrame = false;
			currentTime.restart();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					_running = false;
				}
				else if (event.type == sf::Event::LostFocus) {
					//sf::Event::
				}
				else if (event.type == sf::Event::GainedFocus) {
					try {
						GameState * gs = dynamic_cast< GameState*>(_currentState);
						if (gs != nullptr) {
							gs->pause();
						}
					}
					catch (const std::bad_cast& cast) {
					}
					
				}
				else {

				}
			}
			elapsedTime = currentTime.getElapsedTime();
			//renderElapsedTime += currentTime.getElapsedTime();

			renderElapsedTimeFloat += currentTime.getElapsedTime().asMicroseconds();
			if (renderElapsedTimeFloat >= 1000.f / renderFPS) {
				_renderFrame = true;
				renderElapsedTimeFloat -= 1000.f / renderFPS;
			}
			else {
				//renderElapsedTimeFloat += elapsedTime.asMicroseconds();
			}
			_run();

			{
				gotoxy(0, 0);
				printf("DT: %3.3lld, %Id, %I64d ---\n", elapsedTime.asSeconds(), elapsedTime.asMilliseconds(), elapsedTime.asMicroseconds());
				printf("RenderDT: %3.3f, Elapsed:%I64d  Con: %3.3f ---\n", renderElapsedTimeFloat, elapsedTime.asMicroseconds(),  (1000.f / renderFPS));

				//printf("%d:%d  Frame: %d ", minute, second, frame);
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
	_currentState->tick(getElapsedTime(), _renderFrame);
}



int64_t StateManager::getElapsedTime() {
	printf("DT -- %d - %d    \n", 1000 / FPS, elapsedTime.asMicroseconds());
	//return std::nearbyint( 1000.0 / FPS);
	if (elapsedTime.asMicroseconds() > 0){
		if (elapsedTime.asMicroseconds() <= std::nearbyint(1000.0 / FPS)) {
			return elapsedTime.asMicroseconds();
		}
		else {
			return std::nearbyint(1000.0 / FPS);
		}
	}
	else {
		return 0;
	}
	

}

int64_t StateManager::getRenderElapsedTime() {
	printf("Render DT -- %d - %d    \n", 1000 / renderFPS, renderElapsedTime.asMicroseconds());
	//return std::nearbyint( 1000.0 / renderFPS);
	return renderElapsedTime.asMicroseconds();
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

void StateManager::resetGameTimer() {
	gameTimer.restart();
}

std::string StateManager::getCurrentGameTimer() {
	
	std::string s;
	char c[26];
	s = gameTimer.getElapsedTime().asSeconds();
	s += ":";
	s += gameTimer.getElapsedTime().asMilliseconds();
	s += ":";
	s += gameTimer.getElapsedTime().asMicroseconds();
	return s;
}
