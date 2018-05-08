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
#include "../Game/Projectile.h"
#include <vector>
//class PlayerDrawableAlert;
//class PlayerDrawableDashPosition;
class ProjectileDrawable : public sf::Drawable {
public:

	ProjectileDrawable();
	ProjectileDrawable(Projectile *projectile);
	~ProjectileDrawable();

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	Projectile * projectile;
	int posX;
	int posY;
	int radius;
	sf::Color projectileColor;
	sf::CircleShape projectileHitboxShape;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Font m_font;
	sf::Text m_text;
	float angleDeg;
	//sf::Shader m_shader;
	//bool m_shaderLoaded;
	//std::vector<PlayerDrawableAlert> m_alerts;
	//std::vector<PlayerDrawableDashPosition> m_dashPositions;
	//void addAlert(std::string text);
};

/*
class PlayerDrawableAlert : public sf::Text {
public:
	PlayerDrawableAlert(const std::string& text, const sf::Font& font, float fontSize);
	~PlayerDrawableAlert() = default;
	int timer;
private:
};


class PlayerDrawableDashPosition {
public:
	PlayerDrawableDashPosition(float x, float y);
	~PlayerDrawableDashPosition() = default;
	int timer;
	float posX;
	float posY;
};
*/

#endif // !__Projectile_Drawable__
