/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameState.h"
#include "../States/StateManager.h"

GameState::GameState(sf::RenderWindow *w)
{
	window = w;
	game = new Game();
	renderer = new GameRenderer(window, game);
	
	p1KeyConfig = new ControllerConfig();
	p1Controller = new GameController(p1KeyConfig, game->getPlayer(1));
	//p1Controller = new GameController(StateManager::getInstance().getControllerConfig(1), game->getPlayer(1));
}

GameState::~GameState()
{
	delete p1KeyConfig;
	delete game;
	delete renderer;
	delete p1Controller;
}

void GameState::tick()
{
	switch (game->gameState)
	{
	case GameCurrentState::RUNNING:
		p1Controller->handleInput();
		//p1Controller->updateConfig();
		game->tick();
		renderer->render();
		p1Controller->viewDebugJoystick();
		break;
	case GameCurrentState::PAUSED:
		break;
	case GameCurrentState::ENDED:
		break;
	default:
		break;
	}

}

Game * GameState::getGame()
{
	return game;
}

void GameState::pause() {

}

