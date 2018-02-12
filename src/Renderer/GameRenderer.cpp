/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameRenderer.h"

GameRenderer::GameRenderer()
{
	
}

GameRenderer::GameRenderer(sf::RenderWindow *w, Game *g):
	window(w),
	game(g)
{
	initRenderer();
}

GameRenderer::~GameRenderer()
{
}

void GameRenderer::render()
{
	clear();
	draw();
	display();
}

bool GameRenderer::initRenderer() {
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(100, 100);
	shape.setRadius(size);

	playerDrawable1 = new PlayerDrawable(game->getPlayer(1));
	bool success = false;
	
	return success;
}

void GameRenderer::clear() {
	window->clear();
}

void GameRenderer::draw()
{
	drawPlayers();
	//window->draw(shape);
}

void GameRenderer::display() {
	window->display();
	//lastFrame.update(*(window));
}

void GameRenderer::drawPlayers()
{
	playerDrawable1->update();
	window->draw(*playerDrawable1);
}

void GameRenderer::addGame(Game* g) {
	game = g;
}
void GameRenderer::addWindow(sf::RenderWindow* g) {
	window = g;
}
sf::Texture GameRenderer::getLastFrame() {
	return lastFrame;
}
