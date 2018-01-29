#include "MenuItemDrawable.h"

MenuItemDrawable::MenuItemDrawable() :
item(nullptr){

}


MenuItemDrawable::MenuItemDrawable(MenuItem *menuItem):
	item(menuItem)
{
	if (item != NULL) {

	}
}

MenuItemDrawable::~MenuItemDrawable() {

}

void MenuItemDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

bool MenuItemDrawable::onLoad()
{
	return false;
}

void MenuItemDrawable::onUpdate(float time, float x, float y)
{
}

void MenuItemDrawable::onDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
