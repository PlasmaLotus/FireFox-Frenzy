#include "GameDrawable.h"

GameDrawable::GameDrawable(bool hitboxDisplay):
	_displayHitboxes{hitboxDisplay}
{
	mViewSize = sf::Vector2f(0.f, 0.f);
	mViewCenter = sf::Vector2f(0.f, 0.f);
}

GameDrawable::~GameDrawable()
{
}

void GameDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const{
}

bool GameDrawable::onLoad(){
	return true;
}

void GameDrawable::update(){
}

void GameDrawable::setViewSettings(sf::Vector2f const & viewCenter, sf::Vector2f const & viewSize)
{
	mViewSize = viewSize;
	mViewCenter = viewCenter;
}

void GameDrawable::setDisplayHitboxes(bool display)
{
	_displayHitboxes = display;
}