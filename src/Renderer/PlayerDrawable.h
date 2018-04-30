/*
Created by PlasmaLotus
Updated Feb 11, 2018
*/



#ifndef __Player_Drawable__
#define __Player_Drawable__
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Game/Player.h"
#include <vector>
class PlayerDrawableAlert;
class PlayerDrawable : public sf::Drawable {
public:

	PlayerDrawable();
	PlayerDrawable(Player *player);
	~PlayerDrawable();

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	Player *player;
	int posX;
	int posY;
	int width;
	int height;
	sf::Color playerColor;
	sf::RectangleShape playerShape;
	sf::CircleShape cursorShape;
	std::vector<sf::RectangleShape>dashOffsetShapes;

	sf::Texture rTexture;
	sf::Sprite sprite;

	sf::Font m_font;
	sf::Text m_hpText;
	sf::Text m_dashText;
	sf::Text m_shotText;
	sf::Text m_ammoText;
	int _hp{ 0 };
	bool isChargingDash{ false };
	bool isChargingShot{ false };
	float angleDeg;
	//sf::Shader m_shader;
	//bool m_shaderLoaded;
	std::vector<PlayerDrawableAlert> m_alerts;
	void addAlert(std::string text);
};


class PlayerDrawableAlert : public sf::Text {
public:
	PlayerDrawableAlert(const std::string& text, const sf::Font& font, float fontSize);
	~PlayerDrawableAlert() = default;
	int timer;
private:
};


#endif // !__Player_Renderer__
