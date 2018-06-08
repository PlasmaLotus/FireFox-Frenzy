/*
Created by PlasmaLotus
Updated Mai 7, 2018
*/

#ifndef __Projectile_Drawable__
#define __Projectile_Drawable__
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../../Game/Projectile.h"
#include "GameDrawable.h"
//class PlayerDrawableAlert;
//class PlayerDrawableDashPosition;
class ProjectileDrawable : public GameDrawable {
public:

	ProjectileDrawable(Projectile *projectile, sf::Texture& tx);
	~ProjectileDrawable();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	virtual void update();
	Projectile * projectile;
	int posX;
	int posY;
	int radius;
	sf::Color projectileColor;
	sf::CircleShape projectileHitboxShape;
	sf::Texture& m_texture;
	//sf::Font& m_font;
	sf::Sprite m_sprite;

	sf::Text m_text;
	float angleDeg;
	bool _inView{ true };
};

#endif // !__Projectile_Drawable__
