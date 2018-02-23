/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameLogic.h"
#include "../Main.h"
#include "../States/StateManager.h"
GameLogic::GameLogic():
gameState(GameCurrentState::RUNNING){
	//window.create(sf::VideoMode(800, 600), "SFML! Y U NO DRAW BLOCK!!");
}

GameLogic::~GameLogic(){
	//window.close();
}

void GameLogic::reset() {
}

void GameLogic::tick() {
	frame++;
	dt = StateManager::getInstance().getElapsedTime();
	p1.update(dt);
	printf("GameTick:  DT - %d\n");
}

void GameLogic::pause() {

}

Player * GameLogic::getPlayer(int playerNumber)
{
	return &p1;
}

Player GameLogic::getPlayerCopy(int playerNumber)
{
	return p1;
}
