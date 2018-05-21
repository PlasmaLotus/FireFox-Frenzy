/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameState.h"
#include "../States/StateManager.h"
#include "../States/PauseMenuState.h"
//#include "../Menu/PauseMenu.h"
#include "../States/EndGamePauseMenuState.h"

GameState::GameState(sf::RenderWindow *w):
	State(){
	window = w;
	game = new GameLogic();
	renderer = new GameRenderer(window, game);
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new GameController(this, p1KeyConfig, game->getPlayer(1));
	p2KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(2));
	p2Controller = new GameController(this, p2KeyConfig, game->getPlayer(2));
	StateManager::getInstance().eventManager.setRenderer(renderer);
}

GameState::~GameState(){
	if (pauseMenuState != nullptr) {
		delete pauseMenuState;
	}
	delete p1Controller;
	delete p1KeyConfig;
	delete p2Controller;
	delete p2KeyConfig;
	delete renderer;
	delete game;

}

void GameState::tick(int dt, bool render){
	switch (game->gameState)
	{
	case::GameCurrentState::COUNTDOWN: 
		game->tick(dt);
		renderer->render();
		
		break;
	case GameCurrentState::RUNNING:
		p1Controller->handleInput();
		p2Controller->handleInput();
		//p2Controller->viewDebugJoystick();
		game->tick(dt);
		if (render) {
			renderer->render();
		}
		//printf("GAME TIMER == %s\n", StateManager::getInstance().getCurrentGameTimer());
		break;
	case GameCurrentState::PAUSED:
		printf("===== GAME PAUSED =====\n");
		/*
		if (gameFrame == nullptr) {
			gameFrame = renderer->getLastFrame();
		}
		*/
		window->draw(renderer->renderFrame());
		//renderer->render();
		//window->draw(*gameFrame);
		//window->
		if (pauseMenuState != nullptr) {
			pauseMenuState->tick(dt);
		}
		break;
	case GameCurrentState::ENDED:
		printf("===== GAME ENDED =====\n");
		//game->tick(dt);
		p1Controller->handleInput();
		p2Controller->handleInput();
		renderer->render();
		break;
	default:
		break;
	}

	if (_resetBool) {
		_reset();
		_resetBool = false;
	}
}

GameLogic * GameState::getGame(){
	return game;
}

void GameState::pause() {
	
	if (game->gameState != GameCurrentState::PAUSED) {
		if (gameFrame != nullptr) {
			//delete gameFrame;
			gameFrame = nullptr;
		}

		if (game->gameState == GameCurrentState::RUNNING) {
			game->gameState = GameCurrentState::PAUSED;
			//StateManager::getInstance().switchToState(new PauseMenuState(window));
			if (pauseMenuState == nullptr) {
				pauseMenuState = new PauseMenuState(this, window);
				StateManager::getInstance().eventManager.queueEvent(Event(EventType::PauseMenuEnter));
			}
			else {
				delete pauseMenuState;
				pauseMenuState = new PauseMenuState(this, window);
			}
		}
		else if (game->gameState == GameCurrentState::ENDED) {
			game->gameState = GameCurrentState::PAUSED;
			if (pauseMenuState == nullptr) {
				pauseMenuState = new EndGamePauseMenuState(this, window);//END GAME
				StateManager::getInstance().eventManager.queueEvent(Event(EventType::PauseMenuEnter));
			}
			else {
				delete pauseMenuState;
				pauseMenuState = new EndGamePauseMenuState(this, window);
			}
			
		}
		
	}
	else {
		
		if (!game->_gameEnd) {
			game->gameState = GameCurrentState::RUNNING;
		}
		else {
			game->gameState = GameCurrentState::ENDED;
		}
		
	}
	StateManager::getInstance().startTransition();
	//StateManager::getInstance().switchToState(new PauseMenuState(window, new PauseMenu()));
}

void GameState::reset() {
	_resetBool = true;
}

void GameState::_reset() {
	game->reset();
	renderer->reset();
	//p1Controller->setPlayer(game->getPlayer(1));
	//p2Controller->setPlayer(game->getPlayer(2));
	/*
	if (renderer != nullptr) {
		delete renderer;
	}
	*/
	p1Controller->setPlayer(game->getPlayer(1));
	p2Controller->setPlayer(game->getPlayer(2));
	//countdown
	//renderer = new GameRenderer(window, game);
	//renderer->playerDrawable1->setPlayer(game->getPlayer(1));
	//renderer->playerDrawable2->setPlayer(game->getPlayer(2));
}

GameRenderer * GameState::getRenderer()
{
	return renderer;
}
