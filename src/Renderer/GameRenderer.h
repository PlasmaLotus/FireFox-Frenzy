/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#ifndef __GAME_Renderer__
#define __GAME_Renderer__

//#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include <iostream>
#include "../Game/GameLogic.h"
#include "Renderer.h"
#include "GameDrawable/PlayerDrawable.h"
#include "GameDrawable/MapDrawable.h"
#include "ParticleSystem.h"
#include "GameDrawable/ProjectileDrawable.h"
#include "PlayerUIDrawable.h"
#include "GameDrawable/GameItemDrawable.h"
class GameRenderer : public Renderer{
public:

	//void render(int dt);
	//sf::Image render();
	virtual void clear();
	virtual void draw();
	virtual void render();
	virtual void display();
	virtual void update();
	void reset();
	//void _draw(sf::RenderTarget* target);
	//sf::RenderTexture

	void drawPlayers(sf::RenderTarget* target);
	void drawProjectiles(sf::RenderTarget* target);
	void drawMap(sf::RenderTarget* target);
	void drawItems(sf::RenderTarget* target);
	void addGame(GameLogic * g);
	void addWindow(sf::RenderWindow * g);
	void handleViews(sf::RenderTarget* target);
	void drawParticleSystems(sf::RenderTarget* target);
	void updateParticleSystems(int dt);
	void drawUI(sf::RenderTarget* target);
	sf::Sprite renderFrame();
	sf::RenderTexture* getLastFrame();

	GameRenderer();
	GameRenderer(sf::RenderWindow* window, GameLogic* game);
	~GameRenderer();
	//void setBoards(Board b1, Board b2);
	
	virtual bool initRenderer();

	sf::RenderWindow* window;
	GameLogic* game;
	sf::Texture lastFrame;//not implemented
	sf::RenderTexture* _frame;
	bool texturesLoaded = false;
	const float size = 100.f;
	//sf::CircleShape shape(size);
	sf::CircleShape shape;
	MapDrawable* mapDrawable;
	PlayerDrawable * playerDrawable1;
	PlayerDrawable * playerDrawable2;
	PlayerDrawable * playerDrawable3;
	PlayerDrawable * playerDrawable4;
	PlayerUIDrawable* playerUIDrawable;
	sf::View minimapView;
	sf::View mainView;
	std::vector<ParticleSystem*> _particleSystems;
	void addPlayerAlert(Player *p, std::string text);
	void addPlayerAlert(int playerID, std::string text);
	void setDisplayHitboxes(bool value);
	void setDisplayPositions(bool value);
	void setDisplayFPS(bool value);
	void toggleHitboxes();
	void togglePositions();
	void toggleFPS();
	void __showFPS();
	void __showPlayerPositions();
	void playerHitDisplay(float x, float y);
	bool _displayHitboxes;
	bool _displayPositions;
	bool _displayFPS;

	sf::Texture* playerTexture;
	sf::Texture* projectileGeneralTexture;
	sf::Texture* iconBubbleTexture;
	sf::Texture* iconFireTexture;
	sf::Texture* iconRapidTexture;
	sf::Texture* iconDefaultTexture;
	sf::Font* font;

	sf::Vector2f mViewSize;
	sf::Vector2f mViewCenter;

	std::vector <sf::Drawable> mDrawableList;
	//sf::Font& _font{ sf::Font() };
};

#endif // !__Game_Renderer__
