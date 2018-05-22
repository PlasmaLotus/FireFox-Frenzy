#include "MenuItem.h"


/*Under Construction*/

MenuItem::MenuItem(std::string name, command c) :
	_name(name),
	_fn(c),
	_value(0),
	_max(0) {
	_optionType = MenuItemType::NONE;
}

MenuItem::MenuItem(std::string name, int value, int max, MenuItemType type):
_name(name),
_value(value),
_max(max),
 _optionType(type){
	//_optionType = MenuItemType::RANGE; 
}

MenuItem::MenuItem(std::string name, command c, int value, int max,
	MenuItemType type) :
	_optionType(type),
	_name(name),
	_fn(c),
	_value(value),
	_max(max) {

}

MenuItem::~MenuItem() {
}

command MenuItem::getFn() const {
	return _fn;
}

void MenuItem::increase()
{
	if (_value <= _max) {
		_value++;
	}
}

void MenuItem::decrease()
{
	if (_value >= 0) {
		_value--;
	}
	//_fn()
}

/*
void MenuItem::select()
{
}

void MenuItem::handleInput()
{
}
*/
void MenuItem::setMenuType(MenuItemType t)
{
	_optionType = t;
}

MenuItemType MenuItem::getMenuType()
{
	return _optionType;
}

std::string MenuItem::getName()
{
	std::string s = _name;
	return s;
}

const std::string MenuItem::getOptionString() const {
	
	return _name;
}

std::string MenuItem::getRangeString()
{
	return std::string(std::to_string(_value) + "/" + std::to_string(_max));
}

void MenuItem::setFn(command c)
{
	_fn = c;
}

int MenuItem::getRangeValue()
{
	return _value;
}
