/*
Created by PlasmaLotus
Updated Feb 11, 2018
*/



#ifndef __Player_UI_Drawable__
#define __Player_UI_Drawable__
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include "../Game/Player.h"
#include <vector>
class GameLogic;
class PlayerUIDrawable : public sf::Drawable {
public:

	//PlayerDrawable();
	//PlayerUIDrawable(Player *player,Player* player2, sf::Texture& tx, sf::Font ft);
	PlayerUIDrawable(GameLogic* game, Player * pl, Player * pl2, Player* pl3, Player* pl4, sf::Texture & tx, sf::Font ft, sf::View* view);
	~PlayerUIDrawable();

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Virtual functions to be implemented in derived effects
	bool onLoad();
	//void onUpdate(float time) ;
	void update();
	//void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	Player *player;
	Player *player2;
	Player *player3;
	Player *player4;
	GameLogic* game;
	std::vector<Player*> _players;
	int posX;
	int posY;
	int width;
	int height;
	/*
	sf::Color playerColor;
	sf::RectangleShape playerShape;
	sf::CircleShape cursorShape;
	std::vector<sf::RectangleShape>dashOffsetShapes;
	*/

	void setPlayer(Player *p, int pint);


	sf::Font m_font;
	//sf::Font m__font;
	sf::Texture& rTexture;
	/*
	sf::Sprite sprite;

	sf::Text m_hpText;
	sf::Text m_dashText;
	sf::Text m_shotText;
	sf::Text m_ammoText;
	int _hp{ 0 };
	//bool isChargingDash{ false };
	//bool isChargingShot{ false };
	float angleDeg;
	*/
	sf::View* view;
	//sf::Shader m_shader;
	//bool m_shaderLoaded;
	//std::vector<PlayerDrawableAlert> m_alerts;
	//std::vector<PlayerDrawableDashPosition> m_dashPositions;
	//void addAlert(std::string text);
	//void setDisplayHitboxes(bool display);
	//bool _displayHitboxes{ true };
};


#endif // !__Player_Renderer__
