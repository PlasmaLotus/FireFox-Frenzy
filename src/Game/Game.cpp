/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "Game.h"
#include "../Main.h"
#include "../States/StateManager.h"
Game::Game():
gameState(GameCurrentState::RUNNING){
	//window.create(sf::VideoMode(800, 600), "SFML! Y U NO DRAW BLOCK!!");
}

Game::~Game(){
	//window.close();
}

void Game::reset() {
}

void Game::tick() {
	frame++;
	dt = StateManager::getInstance().getElapsedTime();
	p1.update(dt);
	printf("GameTick:  DT - %d\n");
}

void Game::pause() {

}

Player * Game::getPlayer(int playerNumber)
{
	return &p1;
}

Player Game::getPlayerCopy(int playerNumber)
{
	return p1;
}
