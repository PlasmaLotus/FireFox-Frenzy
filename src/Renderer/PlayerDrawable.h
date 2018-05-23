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
class PlayerDrawableDashPosition;
class GameRenderer;
class PlayerDrawable : public sf::Drawable {
public:

	//PlayerDrawable();
	PlayerDrawable(Player *pl, GameRenderer* renderer, sf::Texture& tx, sf::Font ft);
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

	void setPlayer(Player *p);


	sf::Font m_font;
	//sf::Font m__font;
	sf::Texture& rTexture;
	sf::Sprite sprite;

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
	std::vector<PlayerDrawableDashPosition> m_dashPositions;
	void addAlert(std::string text);
	void setDisplayHitboxes(bool display);
	bool _displayHitboxes{ true };
	GameRenderer* renderer;
};


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

#endif // !__Player_Renderer__
