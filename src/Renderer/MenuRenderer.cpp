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
	update();
	draw();
	display();
}

bool MenuRenderer::initRenderer() {
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	shape.setRadius(100.f);
	shape.setFillColor(sf::Color::Red);
	//debugText.setString("Debug Text");
	/*
	debugText.setFillColor(sf::Color::Magenta);
	debugText.setOutlineColor(sf::Color::White);
	debugText.setPosition(sf::Vector2f(100, 100));
	debugText.setCharacterSize(64);
	*/
	nbMenuItems = menu->items.size();

	//if (!font.loadFromFile("Assets\fonts\LemonMilk.LemonMilk.otf")) {
	/*
	if (!font.loadFromFile("Assets/Fonts/LemonMilk/LemonMilk.otf")){
		fontLoaded = false;
		//return EXIT_FAILURE;
		//resources/sansation.ttf
		//fontLoaded = false;
		//sf::Font::
		//font.loadFromMemory("", 367112);
	}
	debugText.setFont(font);
	debugText.setString("Sf Text Test");
	debugText.setCharacterSize(24);
	//debugText.setFillColor(sf::Color::Red);
	debugText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	debugText.setPosition(50, 50);
	*/

	for (int i = 0; i < menu->items.size(); i++) {
		menuItems[i] = sf::RectangleShape(sf::Vector2f(100, 50));
		menuItems[i].setPosition(50, i * 100);
		//menuItems[i].setFillColor(sf::Color::Magenta);
		_menuItems.push_back(MenuItemDrawable(&menu->items.at(i), 50, i*100));
		//_menuItems[i].setFont(font);
	}
	bool success = false;

	return success;
}


void MenuRenderer::clear() {
	window->clear();
}

void MenuRenderer::update() {
	for (int i = 0; i < menu->items.size(); i++) {
		if (menu->selection == i) {
			_menuItems.at(i).isSelected(true);
		}
		else {
			_menuItems.at(i).isSelected(false);
		}
		_menuItems.at(i).update();
	}
}
void MenuRenderer::draw()
{
	//window->draw(shape);
	/*
	sf::Font font;
	*/
	int y = 100;

	for (unsigned i = 0; i < menu->items.size(); ++i) {
		y += 18;
		/*
		std::string text = "XDXDXDXD";
		sf::Text textDrawable;
		textDrawable.setString("XDXDXDXD");
		textDrawable.setFillColor(sf::Color::Magenta);
		textDrawable.setPosition(sf::Vector2f(20, y));
		window->draw(textDrawable);
		*/
	}

	//window->draw(debugText);
	for (int i = 0; i < menu->items.size(); i++) {
		if (menu->selection == i){
			menuItems[i].setFillColor(sf::Color::Cyan);
		}
		else {
			menuItems[i].setFillColor(sf::Color::Magenta);
		}
		window->draw(_menuItems.at(i));
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

