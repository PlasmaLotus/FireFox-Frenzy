/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "MenuRenderer.h"

MenuRenderer::MenuRenderer()
{
}

MenuRenderer::MenuRenderer(sf::RenderWindow *w, Menu *m):
	window(w),
	menu(m)
{
	initRenderer();
}

MenuRenderer::~MenuRenderer()
{
}

void MenuRenderer::render()
{
	clear();
	draw();
	display();
}

bool MenuRenderer::initRenderer() {
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	shape.setRadius(100.f);
	//sf::CircleShape
	shape.setFillColor(sf::Color::Red);
	debugText.setString("Debug Text");
	debugText.setFillColor(sf::Color::Magenta);
	debugText.setOutlineColor(sf::Color::White);
	debugText.setPosition(sf::Vector2f(100, 100));
	debugText.setCharacterSize(64);
	nbMenuItems = menu->items.size();
	for (int i = 0; i < menu->items.size(); i++) {
		menuItems[i] = sf::RectangleShape(sf::Vector2f(100, 50));
		menuItems[i].setPosition(50, i * 100);
		//menuItems[i].setFillColor(sf::Color::Magenta);
	}
	bool success = false;

	//test.
	return success;
}


void MenuRenderer::clear() {
	window->clear();
}

void MenuRenderer::draw()
{
	//window->draw(shape);
	sf::Font font;
	font.loadFromFile("assets/fonts/LemonMilk/LemonMilk.otf");
	int y = 100;
	for (unsigned i = 0; i < menu->items.size(); ++i) {
		y += 18;
		//std::string text();
		std::string text = "XDXDXDXD";
		sf::Text textDrawable;
		textDrawable.setString("XDXDXDXD");
		textDrawable.setFillColor(sf::Color::Magenta);
		textDrawable.setPosition(sf::Vector2f(20, y));
		window->draw(textDrawable);
	}
	window->draw(debugText);
	for (int i = 0; i < menu->items.size(); i++) {
		if (menu->selection == i){
			menuItems[i].setFillColor(sf::Color::Cyan);
		}
		else {
			menuItems[i].setFillColor(sf::Color::Magenta);
		}
		window->draw(menuItems[i]);
	}

}

void MenuRenderer::display() {
	window->display();
}
void MenuRenderer::addMenu(Menu * m)
{
	menu = m;
}
void MenuRenderer::addWindow(sf::RenderWindow* g) {
	window = g;
}
sf::Texture MenuRenderer::getLastFrame() {
	return lastFrame;
}

