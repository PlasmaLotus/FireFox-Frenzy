/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameRenderer.h"

GameRenderer::GameRenderer()
{
	
}

GameRenderer::GameRenderer(sf::RenderWindow *w, GameLogic *g):
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
	playerDrawable2 = new PlayerDrawable(game->getPlayer(2));
	playerDrawable2->playerColor = sf::Color::Magenta;
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
	playerDrawable2->update();
	window->draw(*playerDrawable2);

	for (int i = game->_entities.size() - 1; i >= 0; i--) {
		Entity *e = game->_entities.at(i);
		try
		{
			Projectile *p = dynamic_cast<Projectile *>(e);
			if (p != nullptr) {
				sf::CircleShape c(1);
				c.setFillColor(sf::Color::White);
				c.setRadius(p->width / 2);
				c.setOutlineColor(sf::Color::Red);
				c.setPosition(sf::Vector2f(p->posX - p->width / 2, p->posY - p->width / 2));
				window->draw(c);
			}
		}
		catch (const std::bad_cast& cast)
		{

		}
	}
}

void GameRenderer::addGame(GameLogic* g) {
	game = g;
}
void GameRenderer::addWindow(sf::RenderWindow* g) {
	window = g;
}
sf::Texture GameRenderer::getLastFrame() {
	return lastFrame;
}
