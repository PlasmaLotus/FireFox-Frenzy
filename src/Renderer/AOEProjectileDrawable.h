/*
Created by PlasmaLotus
Updated Mai 7, 2018
*/



#ifndef __AOEProjectile_Drawable__
#define __AOEProjectile_Drawable__
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Game/Projectiles/AOEProjectile.h"
#include <vector>
//class PlayerDrawableAlert;
//class PlayerDrawableDashPosition;
class AOEProjectileDrawable : public sf::Drawable {
public:

	//ProjectileDrawable();
	AOEProjectileDrawable(AOEProjectile *projectile, sf::Texture& tx);
	~AOEProjectileDrawable();

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	AOEProjectile * projectile;
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
	void setDisplayHitboxes(bool display);
	bool _displayHitboxes{ true };

};


#endif // !__Projectile_Drawable__
