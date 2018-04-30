/*
Created by PlasmaLotus
Updated May 13, 2017
*/
#include "GameRenderer.h"
#include "../States/StateManager.h"

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
	mapDrawable = new MapDrawable(&game->map);
	playerDrawable1 = new PlayerDrawable(game->getPlayer(1));
	playerDrawable2 = new PlayerDrawable(game->getPlayer(2));
	playerDrawable2->playerColor = sf::Color::Magenta;
	
	_displayFPS = true;
	_displayPositions = true;
	_displayHitboxes = true;

	if (!font.loadFromFile("Assets/Fonts/Minecraft.ttf"))
		success = false;
	/*
	// player 1 (left side of the screen)
	p1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));

	// player 2 (right side of the screen)
	p2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
	*/

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
	mainView = sf::View(sf::Vector2f(1080 / 2, 720 / 2), sf::Vector2f(1080, 720));
	window->setView(mainView);
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

void GameRenderer::setDisplayHitboxes(bool value){
	_displayHitboxes = value;
}

void GameRenderer::setDisplayPositions(bool value){
	_displayPositions = value;
}

void GameRenderer::setDisplayFPS(bool value){
	_displayFPS = value;
}

void GameRenderer::clear() {
	window->clear();
}

void GameRenderer::draw(){
	drawMap();
	drawProjectiles();
	drawItems();
	drawPlayers();
	
	handleViews();
	__showFPS();
	__showPlayerPositions();
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
	/*
	Map map = game->map;
	sf::RectangleShape mapOutline;
	mapOutline.setSize(sf::Vector2f(map.width, map.height));
	mapOutline.setPosition(0, 0);
	mapOutline.setOutlineColor(sf::Color::White);
	//mapOutline.setFillColor(sf::Color(200, 200, 200, 150));
	mapOutline.setFillColor(sf::Color(0, 0, 0, 0));
	mapOutline.setOutlineThickness(5.0f);
	window->draw(mapOutline);
	*/

	mapDrawable->update();
	window->draw(*mapDrawable);
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
	Player*p1 = game->getPlayer(1);
	Player*p2 = game->getPlayer(2);

	float minX, minY, maxX, maxY, distX, distY;
	maxX = std::max(p1->posX, p2->posX);
	maxY = std::max(p1->posY, p2->posY);
	minX = std::min(p1->posX, p2->posX);
	minY = std::min(p1->posY, p2->posY);
	distX = abs(p1->posX - p2->posX);
	distY = abs(p1->posY - p2->posY);
	/*
	//p1View.move(p->posX - p->prevPosX, p->posY - p->prevPosY);
	p1View.setCenter(playerDrawable1->player->posX, playerDrawable1->player->posY);
	p2View.setCenter(playerDrawable2->player->posX, playerDrawable2->player->posY);
	*/

	//mainView.setViewport(sf::FloatRect(minX, minY, maxX - minX + 100, maxY - minY + 100));
	float some = 1280.f * 9.f / 16.f;
	float extraRoom = 360.f;
	//if (distX > window->getSize().x * 0.8f || distY > window->getSize().y  * 0.8f) {
		float newDistX = distX;
		float newDistY =  distY;
		if (distY * 16.f / 9.f > distX) {
			newDistX = distY * 16.f / 9.f;
			newDistY = newDistX * 9.f / 16.f;
		}
		if (distX * 9.f / 16.f > distY) {
			newDistY = distX * 9.f / 16.f;
			newDistX = newDistY * 16.f / 9.f;
		}
	
		//if (newDistX < 1280 && newDistY < 720) {
		if (newDistX < StateManager::getWindowWidth() && newDistY < StateManager::getWindowHeight()) {
			newDistX = 1.0f * StateManager::getWindowWidth();
			newDistY = 1.0f * StateManager::getWindowHeight();
		}
		sf::Vector2f viewSize(newDistX + extraRoom * 16.f / 9.f, newDistY + extraRoom * 9.f / 16.f);
		mainView.setSize(viewSize);
		//mainView.setSize(sf::Vector2f(newDistX + extraRoom * 16.f / 9.f , newDistY + extraRoom * 9.f / 16.f));
		
		///TODO Limit 
		///Limit camera dependant of  map;
		sf::Vector2f viewCenter(1.0f * distX / 2.f + minX, 1.0f * distY / 2.f + minY);
		if (viewCenter.x < window->getSize().x /2.f || viewCenter.y < window->getSize().y /2.f) {
			if (viewCenter.x < window->getSize().x /2.f) {
				viewCenter.x = window->getSize().x / 2.f;
			}
			if (viewCenter.y < window->getSize().y /2.f) {
				viewCenter.y = window->getSize().y / 2.f;
			}
		}
		
		mainView.setCenter(viewCenter);
		//mainView.setCenter(sf::Vector2f(1.0f * distX / 2.f + minX, 1.0f * distY / 2.f + minY));
		//mainView.setCenter(sf::Vector2f(1.0f * newDistX / 2.f + minX, 1.0f * newDistY / 2.f + minY));
	//}

	/*
	else {
		//mainView.setSize(sf::Vector2f(window->getSize().x, distY > window->getSize().y));
		mainView.setSize(sf::Vector2f(1280.f, 720.f));
		//mainView.setCenter(sf::Vector2f(540, 360));
		//mainView.set
		mainView.setCenter(sf::Vector2f(1.0f * distX / 2.f + minX, 1.0f * distY / 2.f + minY));	
	}
	*/
	
	//mainView.setCenter(p1->posX, p1->posY);
	window->setView(mainView);
}
sf::Texture GameRenderer::getLastFrame() {
	return lastFrame;
}

void GameRenderer::__showFPS() {
	if (_displayFPS) {
		int windowY = window->getView().getCenter().y - window->getView().getSize().y / 2;
		int windowX = window->getView().getCenter().x - window->getView().getSize().x / 2;
		int fontSize = window->getView().getSize().x / 100;

		sf::Text fpsText("", playerDrawable1->m_font, fontSize);
		std::string fpsstring = "FPS: ";
		fpsstring += std::to_string(StateManager::getInstance().getFrameRate());
		fpsstring += " / ";
		fpsstring += std::to_string(StateManager::getInstance().FPS);
		fpsText.setString(fpsstring);
		//playerText1.setFont()
		fpsText.setFillColor(sf::Color::Magenta);
		fpsText.setPosition(windowX + 2, windowY + 2);
		window->draw(fpsText);
	}
}

void GameRenderer::__showPlayerPositions() {
	if (_displayPositions) {

		/*
		int windowY = window->getView().getViewport().top;
		int windowX = window->getView().getViewport().left;
		*/

		int windowY = window->getView().getCenter().y - window->getView().getSize().y / 2;
		int windowX = window->getView().getCenter().x - window->getView().getSize().x / 2;
		int fontSize = window->getView().getSize().x / 100;

		sf::Text playerText1("", playerDrawable1->m_font, fontSize);
		//playerText1.setFont()
		playerText1.setFillColor(sf::Color::Magenta);
		playerText1.setString("P1 - X: " + std::to_string((int)playerDrawable1->player->posX) + " Y: " + std::to_string((int)playerDrawable1->player->posY));
		playerText1.setPosition(windowX + 2, windowY + fontSize*2 + 2);
		window->draw(playerText1);


		sf::Text playerText2("", playerDrawable2->m_font, fontSize);
		playerText2.setFillColor(sf::Color::Magenta);
		playerText2.setString("P2 - X: " + std::to_string((int)playerDrawable2->player->posX) + " Y: " + std::to_string((int)playerDrawable2->player->posY));
		playerText2.setPosition(windowX + 2, windowY + fontSize*3 + 2);
		window->draw(playerText2);
	}
}