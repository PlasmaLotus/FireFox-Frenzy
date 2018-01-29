/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "Game.h"
#include "../Main.h"
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
	printf("GameTick\n");
}

void Game::pause() {

}