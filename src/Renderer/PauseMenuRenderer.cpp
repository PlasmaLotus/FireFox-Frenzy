/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "PauseMenuRenderer.h"

PauseMenuRenderer::PauseMenuRenderer()
{
}

PauseMenuRenderer::PauseMenuRenderer(sf::RenderWindow *w, Menu *m):
	MenuRenderer(w, m)
{
	initRenderer();
}

PauseMenuRenderer::~PauseMenuRenderer()
{
	_menuItems.clear();
}

void PauseMenuRenderer::render()
{
	//MenuRenderer::render();
	//clear();
	update();
	draw();
	display();
}

bool PauseMenuRenderer::initRenderer() {
	bool success = true;
	nbMenuItems = menu->items.size();
	int menuItemTabulation = 25;

	_windowHeight = window->getDefaultView().getSize().y;
	_windowWidth = window->getDefaultView().getSize().x;

	background = sf::RectangleShape(sf::Vector2f(_windowWidth, _windowHeight));
	background.setFillColor(sf::Color(255, 255, 255, 100));
	background.setPosition(0, 0);
	
	foreground = sf::RectangleShape(sf::Vector2f(_windowWidth/2, _windowHeight * 10.f/ nbMenuItems + nbMenuItems *menuItemTabulation));
	foreground.setFillColor(sf::Color(255, 255, 255, 200));
	foreground.setOrigin(foreground.getSize().x / 2, foreground.getSize().y / 2);
	foreground.setPosition(_windowWidth / 2, _windowHeight / 2);
	
	if (!font.loadFromFile("Assets\fonts\Minecraft.ttf")) {
		success = false;
		fontLoaded = false;
	}
	
	int menuItemWidth = 100;
	int menuItemHeight = 50;
	int menuItemPosX = _windowWidth / 2 - menuItemWidth / 2;
	int menuItemPosYOrigin = foreground.getPosition().y - foreground.getSize().y / 2;
	for (int i = 0; i < menu->items.size(); i++) {
		menuItems[i] = sf::RectangleShape(sf::Vector2f(menuItemWidth, menuItemHeight));
		menuItems[i].setPosition(menuItemPosX, i * menuItemHeight + (i + 1) * menuItemTabulation);
		_menuItems.push_back(MenuItemDrawable(&menu->items.at(i), menuItemPosX, i * menuItemHeight + (i + 1) * menuItemTabulation));
	}

	return success;
}


void PauseMenuRenderer::clear() {
	window->clear();
}

void PauseMenuRenderer::update() {
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
void PauseMenuRenderer::draw()
{
	int y = 100;

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

void PauseMenuRenderer::display() {
	window->display();
}
