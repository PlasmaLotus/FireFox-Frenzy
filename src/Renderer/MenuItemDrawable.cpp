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
	shape = sf::RectangleShape(sf::Vector2f(75, 50));
	shape.setPosition(posX, posY);
	shape.setFillColor(sf::Color::Red);
	
	//if (!m_font.loadFromFile("./Assets/fonts/Minecraft.ttf")) {
	if (!m_font.loadFromFile("./Assets/fonts/arial.ttf")) {
		printf("Unable to load Font\n");
	}
	
	m_menuItemText = sf::Text("MenuItem", m_font, 12);
	m_menuItemText2 = sf::Text("Text2", m_font, 12);
	m_menuItemText.setFillColor(sf::Color::Black);
	m_menuItemText2.setFillColor(sf::Color::Black);

	//s1.setFont(*_font);
	//s2.setFont(*_font);
	/*
	s1.setFont(font);
	s2.setFont(font);
	
	s1.setFillColor(sf::Color::Black);
	s2.setFillColor(sf::Color::Black);
	*/
	width = 10;
	height = 10;
	
	shape.setSize(sf::Vector2f(width, height));

}

MenuItemDrawable::~MenuItemDrawable() {

}

void MenuItemDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape, states);
	sf::Text t("MenuItemSoloTest", m_font, 24);
	t.setPosition(posX + 15, posY + 15);
	if (item != NULL) {
		t.setString(item->getOptionString());
	}
	t.setFillColor(sf::Color::Black);
	target.draw(t);

	sf::Text t2(itemOption, m_font, 18);
	t2.setPosition(posX + 15, posY + 40);
	t2.setFillColor(sf::Color::Black);
	//target.draw(m_menuItemText);
	target.draw(t2);
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
	if (item != NULL) {
		//str1 = item->getOptionString();
		std::string itemName = item->getName();
		m_menuItemText.setString( "Test");
		m_menuItemText2.setString("Test2");

		m_menuItemText.setPosition(sf::Vector2f(posX + 15, posY + 15));
		m_menuItemText2.setPosition(sf::Vector2f(posX + 150, posY + 15));

		switch (item->getMenuType()) {
		case MenuItemType::TOGGLE: {
			//str2 = "off";
			m_menuItemText2.setString("Toggle");
			itemOption = "Toggle";
			height = 50;
			width = 400;
			/*
			s1.setCharacterSize(14);
			s2.setCharacterSize(14);
			*/
			break;
		}
		case MenuItemType::RANGE:
		{
			itemOption = item->getRangeString();
			//m_menuItemText2.setString(str2);
			height = 100;
			width = 200;
			/*
			s1.setCharacterSize(22);
			*/
			break;
		}
		case MenuItemType::NONE:
		default: {
			//str2 = "";
			//m_menuItemText2.setString("null");
			height = 100;
			width = 200;
			/*
			s1.setCharacterSize(22);
			*/
			break;
		}

		}

	}
	shape.setSize(sf::Vector2f(width, height));
}

void MenuItemDrawable::isSelected(bool value)
{
	if (_isSelected != value) {

	}
	_isSelected = value;
}

void MenuItemDrawable::setFont(sf::Font & f)
{
	//_font = &f;
}
