/*
Created by PlasmaLotus
Updated May 13, 2017
*/
#include "GameRenderer.h"

GameRenderer::GameRenderer(){
}

GameRenderer::GameRenderer(sf::RenderWindow *w, GameLogic *g):
	window(w),
	game(g){
	initRenderer();
}

GameRenderer::~GameRenderer(){
}

void GameRenderer::render(){
	clear();
	draw();
	display();
}

bool GameRenderer::initRenderer() {
	bool success = true;
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(100, 100);
	shape.setRadius(size);

	playerDrawable1 = new PlayerDrawable(game->getPlayer(1));
	playerDrawable2 = new PlayerDrawable(game->getPlayer(2));
	playerDrawable2->playerColor = sf::Color::Magenta;
	
	if (!font.loadFromFile("Assets/Fonts/LemonMilk/LemonMilk.otf"))
		success = false;

	return success;
}

void GameRenderer::clear() {
	window->clear();
}

void GameRenderer::draw(){
	drawPlayers();
	drawProjectiles();
}

void GameRenderer::display() {
	window->display();
}

void GameRenderer::drawPlayers(){
	playerDrawable1->update();
	window->draw(*playerDrawable1);
	playerDrawable2->update();
	window->draw(*playerDrawable2);
}

void GameRenderer::drawProjectiles(){
	std::vector<Entity*> vec = game->_entities;
	for (int i = 0; i < vec.size(); i++) {
		try {
			Projectile * p = dynamic_cast<Projectile *> (vec.at(i));
			if (p != nullptr) {
				sf::CircleShape circle;
				circle.setFillColor(sf::Color::Green);
				circle.setPosition(p->posX, p->posY);
				circle.setRadius(p->width);
				window->draw(circle);
			}
		}
		catch (const std::bad_cast& cast){
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
