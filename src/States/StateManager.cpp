#include "StateManager.h"
#include "GameState.h"

StateManager::StateManager() :
	_currentState(NULL),
	_newState(NULL),
	_switchState(false),
	_deletedState(false),
	_stateTransition(false),
	_backToTitle(false),
	_stateTransitionTime(0),
	//m_alertManager("Assets/Fonts/Minecraft.ttf", 18, window.getView().getSize())
	m_alertManager("Assets/Fonts/arial.ttf", 18, window.getView().getSize())
{
	//window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Neon Galaxy");
	window.create(sf::VideoMode::getFullscreenModes()[0], "Neon Galaxy", sf::Style::Fullscreen);

	_currentState = new TitleScreen(&window);
	_states.push(_currentState);
	eventManager.setAudioEventManager(&audioEventManager);
	//m_alertManager = Alerts("Assets\fonts\Minecraft.ttf", 18, window.getSize());
	FreeConsole();
}

int StateManager::getWindowWidth()
{
	return StateManager::getInstance().window.getSize().x;
}

int StateManager::getWindowHeight()
{
	return StateManager::getInstance().window.getSize().y;
}

StateManager::~StateManager(){
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
	startTransition();
}

void StateManager::goBack() {
	_deletedState = true;
	startTransition();
	/*
	*/
}

void StateManager::goBackTo(State *state) {
	std::stack<State* > tempStack;
	State *temp = _states.top();
	if (temp != state) {
		bool found = false;
		tempStack.push(temp);
		while (!found) {
			_states.pop();
			temp = _states.top();
			if (temp == state) {
				found = true;
			}
			else {
				tempStack.push(temp);
				if (_states.size() <= 0) {
					break;
				}
			}
		}
		if (_states.size() <= 0) {
			while (tempStack.size() > 0) {
				_states.push(tempStack.top());
				tempStack.pop();
			}
		}

	}

	/*
	for (int i = 0; i­ < howMany; ++i) {
		goBack();
	}
	*/
	//startTransition();
}

void StateManager::goBackToTitle(){
	window.setView(window.getDefaultView());
	if (_states.size() > 1) {
		//_removeFromStack();
		_deletedState = true;
		_backToTitle = true;
	}
	else {
		_backToTitle = false;
		startTransition();
	}

}

void StateManager::_removeFromStack(){
	if (_states.size() > 1) {
		State * s = _states.top();
		delete s;
		_states.pop();
		_currentState = _states.top();
	}
	else {
		//Quit?
	}
}

void StateManager::quit() {
	_running = false;
}

void StateManager::startTransition(){
	_stateTransition = true;
	_stateTransitionTime = 1000;//1 second
	_stateTransitionTimer.restart();
}

void StateManager::setScreenDimensions(int x, int y)
{
}

void StateManager::setDisplayFPS(bool state)
{
	_displayFPS = state;
}

void StateManager::setDisplayHitboxes(bool state)
{
	_displayHitboxes = state;
}

void StateManager::setDisplayPlayerPositions(bool state)
{
	_displayPlayerPos = state;
}

bool StateManager::getDisplayFPS()
{
	return _displayFPS;
}

bool StateManager::getDisplayHitboxes()
{
	return _displayHitboxes;
}

bool StateManager::getDisplayPlayerPositions()
{
	return _displayPlayerPos;
}

sf::RenderWindow *StateManager::getWindow() {
	return &window;
}

void StateManager::run(){
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
					/*
				try {
					GameState * gs = dynamic_cast< GameState*>(_currentState);
					if (gs != nullptr) {
						gs->pause();
					}
				}
				catch (const std::bad_cast& cast) {
				}
					*/
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

		if (_switchState) {
			_states.push(_newState);
			//delete _currentState;
			_currentState = _newState;
			_switchState = false;
			_newState = nullptr;
			window.clear();
		}

		if (_deletedState) {
			_removeFromStack();
			_deletedState = false;
			goBackToTitle();
			window.clear();
		}
		else {
			if (_stateTransition) {
				_stateTransitionTime -= elapsedTime.asMicroseconds();
				//_stateTransitionTimer += currentTime.getElapsedTime();
				//if (_stateTransitionTime <= 0) {
				if (_stateTransitionTimer.getElapsedTime() >= sf::milliseconds(200)){
					_stateTransition = false;
					_stateTransitionTime = 0;
					_stateTransitionTimer.restart();
				}
				window.clear();
			}
			else {
				_run();
			}
		}
		{
			gotoxy(0, 0);
			printf("DT: %3.3lld, %Id, %I64d ---\n", elapsedTime.asSeconds(), elapsedTime.asMilliseconds(), elapsedTime.asMicroseconds());
			printf("RenderDT: %3.3f, Elapsed:%I64d  Con: %3.3f ---\n", renderElapsedTimeFloat, elapsedTime.asMicroseconds(),  (1000.f / renderFPS));
			printf("NB Frames: %3.8f     Temps: %d    Clocks per Sec: %3.2f\n",
				(float)elapsedTime.asMilliseconds() * 60, elapsedTime.asMilliseconds(), (float)CLOCKS_PER_SEC);
		}

		_runHandlers();
			
	}
	return;
}

void StateManager::_run() {
	window.clear();
	//eventManager.handleEvents(getElapsedTime());
	//audioEventManager.handleEvents(getElapsedTime());
	//window.draw(m_alertManager);
	//_currentState->tick(getElapsedTime(), _renderFrame);
	if (_states.size() > 0){
		_states.top()->tick(getElapsedTime(), true);
		//_states.top()->tick(getElapsedTime(), _renderFrame);
	}
	m_alertManager.update(getElapsedTime(), window);
	//window.draw(m_alertManager);
}
void StateManager::_runHandlers() {

	eventManager.handleEvents(getElapsedTime());
	audioEventManager.handleEvents(getElapsedTime());

}

int64_t StateManager::getElapsedTime() {
	//printf("DT -- %d - %d    \n", 1000 / FPS, elapsedTime.asMicroseconds());
	//return std::nearbyint( 1000.0 / FPS);
	if (elapsedTime.asMicroseconds() >= 0){
		if (elapsedTime.asMicroseconds() <= std::nearbyint(1000.0f / FPS)) {
			return elapsedTime.asMicroseconds();
		}
		else {
			return std::nearbyint(1000.0f / FPS);
		}
	}
	else {
		return 0;
	}
}

int64_t StateManager::getRenderElapsedTime() {
	//printf("Render DT -- %d - %d    \n", 1000 / renderFPS, renderElapsedTime.asMicroseconds());
	//return std::nearbyint( 1000.0 / renderFPS);
	return renderElapsedTime.asMicroseconds();
}

int StateManager::getUniqueID() {
	return _id++;
}

ControllerConfig *StateManager::getControllerConfig(int playerNumber){
	if (playerNumber == 1) {
		return &p1Config;
	}
	else {
		return &p2Config;
	}
}

std::string StateManager::getControllerConfigPath(int playerNumber){
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

int StateManager::getFrameRate(){
	return std::nearbyint(1000.0 / elapsedTime.asMicroseconds());
}

int StateManager::getAbsoluteFrameRate(){
	return FPS;
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

void StateManager::toggleHitboxes()
{
	if (_displayHitboxes) {
		setDisplayHitboxes(false);
		m_alertManager.addAlert("HitBox Display turned OFF");
	}
	else {
		setDisplayHitboxes(true);
		m_alertManager.addAlert("HitBox Display turned ON");
	}
}

void StateManager::togglePositions()
{
	if (_displayPlayerPos) {
		setDisplayPlayerPositions(false);
		m_alertManager.addAlert("Player Positions Display turned OFF");
	}
	else {
		setDisplayPlayerPositions(true);
		m_alertManager.addAlert("Player Positions Display turned ON");

	}
}

void StateManager::toggleFPS()
{
	if (_displayFPS) {
		setDisplayFPS(false);
		m_alertManager.addAlert("FPS Display turned OFF");
	}
	else {
		setDisplayFPS(true);
		m_alertManager.addAlert("FPS Display turned ON");

	}
}
