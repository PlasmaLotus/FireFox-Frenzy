#include "MenuItemDrawable.h"

MenuItemDrawable::MenuItemDrawable() :
item(nullptr),
posX(0),
posY(0){

}


MenuItemDrawable::MenuItemDrawable(MenuItem *menuItem, int px, int py):
	sf::Drawable(),
	item(menuItem),
	posX(px),
	posY(py)
{
	shape = sf::RectangleShape(sf::Vector2f(100, 50));
	shape.setPosition(posX, posY);
	shape.setFillColor(sf::Color::Red);
	
	if (font.loadFromFile("./Assets/fonts/arial.ttf")) {
		shape.setFillColor(sf::Color::White);
	}
	//s1.setFont(*_font);
	//s2.setFont(*_font);
	s1.setFont(font);
	s2.setFont(font);
	
	s1.setFillColor(sf::Color::Black);
	s2.setFillColor(sf::Color::Black);
	if (item != NULL) {
		//str1 = item->getOptionString();
		std::string itemName = item->getName();
		s1.setString("Test");
		s1.setPosition(posX+ 15, posY+15);
		s2.setPosition(posX + 150, posY + 15);
		switch (item->getMenuType()) {
		case MenuItemType::TOGGLE: {
			//str2 = "off";
			s2.setString("off");
			height = 50;
			width = 400;
			
			s1.setCharacterSize(14);
			s2.setCharacterSize(14);
			break;
		}
		case MenuItemType::NONE:
		default: {
			//str2 = "";
			s2.setString("null");
			height = 100;
			width = 200;
			s1.setCharacterSize(22);
			break;
		}

		}

	}

	shape.setSize(sf::Vector2f(width, height));

}

MenuItemDrawable::~MenuItemDrawable() {

}

void MenuItemDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape, states);
	//target.draw(s1, states);
	//target.draw(s2, states);
	//target.
}

bool MenuItemDrawable::onLoad()
{
	return false;
}

void MenuItemDrawable::update()
{
	if (_isSelected) {
		shape.setFillColor(sf::Color::Cyan);
	}
	else {
		shape.setFillColor(sf::Color::Red);
	}

}

void MenuItemDrawable::isSelected(bool value)
{
	if (_isSelected != value) {

	}
	_isSelected = value;
}

void MenuItemDrawable::setFont(sf::Font & f)
{
	_font = &f;
}
