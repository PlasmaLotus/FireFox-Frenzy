/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameState.h"
#include "../States/StateManager.h"

GameState::GameState(sf::RenderWindow *w):
	State(),
	eventManager(EventManager::getInstance())
{
	eventManager.setRenderer(renderer);
	eventManager.setGame(game);
	window = w;
	game = new GameLogic();
	renderer = new GameRenderer(window, game);
	//eventManager = 
	p1KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(1));
	p1Controller = new GameController(this, p1KeyConfig, game->getPlayer(1));
	p2KeyConfig = new ControllerConfig(StateManager::getControllerConfigPath(2));
	p2Controller = new GameController(this, p2KeyConfig, game->getPlayer(2));
}

GameState::~GameState()
{
	delete p1Controller;
	delete p1KeyConfig;
	delete p2Controller;
	delete p2KeyConfig;
	delete renderer;
	delete game;
}

void GameState::tick()
{
	switch (game->gameState)
	{
	case GameCurrentState::RUNNING:
		p1Controller->handleInput();
		p2Controller->handleInput();
		game->tick();
		renderer->render();
		eventManager.handleEvents();
		//p1Controller->viewDebugJoystick();
		break;
	case GameCurrentState::PAUSED:
		renderer->render();
		//pauseRenderer->render();
		break;
	case GameCurrentState::ENDED:
		break;
	default:
		break;
	}
}

GameLogic * GameState::getGame()
{
	return game;
}

void GameState::pause() {
	//game->reset();
}

void GameState::reset() {
	game->reset();
	p1Controller->setPlayer(game->getPlayer(1));
	p2Controller->setPlayer(game->getPlayer(2));
}
