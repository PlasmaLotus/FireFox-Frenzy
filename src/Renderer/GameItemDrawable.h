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
#include "../Game/Item.h"
#include "../Game/PowerupItem.h"
#include <vector>
//class PlayerDrawableAlert;
//class PlayerDrawableDashPosition;
class GameItemDrawable : public sf::Drawable {
public:

	//ProjectileDrawable();
	GameItemDrawable(Item *projectile, sf::Texture& tx);
	~GameItemDrawable();

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	Item * item;
	int posX;
	int posY;
	int radius;
	sf::Color itemColor;
	sf::CircleShape itemHitboxShape;
	sf::Texture& m_texture;
	//sf::Font& m_font;
	sf::Sprite m_sprite;

	sf::Text m_text;
	bool _displayHitboxes{ true };

};


#endif // !__Projectile_Drawable__
