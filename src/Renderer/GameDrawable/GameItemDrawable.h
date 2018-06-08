/*
Created by PlasmaLotus
Updated Mai 7, 2018
*/

#ifndef __GAMEITEM_Drawable__
#define __GAMEITEM_Drawable__

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../../Game/Item.h"
#include "../../Game/PowerupItem.h"
#include "GameDrawable.h"
#include <vector>

class GameItemDrawable : public GameDrawable {
public:

	GameItemDrawable(Item *projectile, sf::Texture& tx);
	~GameItemDrawable();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void update();
	Item * item;
	int posX;
	int posY;
	int radius;
	sf::Color itemColor;
	sf::Color itemHitboxColor;
	sf::CircleShape itemHitboxShape;
	sf::Texture& m_texture;
	//sf::Font& m_font;
	sf::Sprite m_sprite;

	sf::Text m_text;

	bool _inView{ true };
};


#endif // !__Projectile_Drawable__
