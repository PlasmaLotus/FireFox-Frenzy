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

	// player 1 (left side of the screen)
	p1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	// player 2 (right side of the screen)
	p2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));

	/*
	p1View.zoom(2.0f);
	p2View.zoom(2.0f);
	*/

	// mini-map (upper-right corner)
	//minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	/*
	window->setView(p1View);
	window->setView(p2View);
	*/
	//window->view
	window->setView(window->getDefaultView());
	//window->setView(minimapView);
	return success;
}

void GameRenderer::addPlayerAlert(Player * p, std::string text){
	if (playerDrawable1->player == p) {
		playerDrawable1->addAlert(text);
	}
	else if (playerDrawable2->player == p) {
		playerDrawable1->addAlert(text);
	}
	else{}
}

void GameRenderer::addPlayerAlert(int playerID, std::string text){
	Player&p = game->findPlayer(playerID);
	addPlayerAlert(&p, text);
}

void GameRenderer::clear() {
	window->clear();
}

void GameRenderer::draw(){
	drawPlayers();
	drawProjectiles();
	drawItems();
	drawMap();
	handleViews();
	//window->draw();
}

void GameRenderer::display() {
	window->display();
}

void GameRenderer::drawPlayers(){
	playerDrawable1->update();
	playerDrawable2->update();
	//window->setView(p1View);
	window->draw(*playerDrawable1);
	window->draw(*playerDrawable2);
	/*
	window->setView(p2View);
	window->draw(*playerDrawable1);
	window->draw(*playerDrawable2);
	*/
}

void GameRenderer::drawProjectiles(){
	std::vector<Entity*> vec = game->_entities;
	for (int i = 0; i < vec.size(); i++) {
		try {
			Projectile * p = dynamic_cast<Projectile *> (vec.at(i));
			if (p != nullptr) {
				sf::CircleShape circle;
				circle.setFillColor(sf::Color::Green);
				circle.setPosition(p->posX - p->width /2, p->posY - p->width / 2);
				circle.setRadius(p->width);
				window->draw(circle);
			}
		}
		catch (const std::bad_cast& cast){
		}
	}
}

void GameRenderer::drawMap()
{
	//Map = game->map;
}

void GameRenderer::drawItems() {
	std::vector<Entity*> vec = game->_entities;
	for (int i = 0; i < vec.size(); i++) {
		try {
			Item * p = dynamic_cast<Item *> (vec.at(i));
			if (p != nullptr) {
				sf::CircleShape circle;
				if (p->state == ItemState::ItemCooldown) {
					circle.setFillColor(sf::Color(100, 100, 100, 100));
				}
				else {
					circle.setFillColor(sf::Color(100, 100,100,200));
				}
				circle.setPosition(p->posX - p->width / 2, p->posY - p->width / 2);
				circle.setRadius(p->width);
				window->draw(circle);
			}
		}
		catch (const std::bad_cast& cast) {
		}
	}
}

void GameRenderer::addGame(GameLogic* g) {
	game = g;
}
void GameRenderer::addWindow(sf::RenderWindow* g) {
	window = g;
}
void GameRenderer::handleViews(){
	//setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	Player*p = game->getPlayer(1);
	//p1View.move(p->posX - p->prevPosX, p->posY - p->prevPosY);
	p1View.setCenter(playerDrawable1->player->posX, playerDrawable1->player->posY);
	p2View.setCenter(playerDrawable2->player->posX, playerDrawable2->player->posY);
}
sf::Texture GameRenderer::getLastFrame() {
	return lastFrame;
}
