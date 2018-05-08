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
#include "PlayerDrawable.h"
#include "MapDrawable.h"
#include "ParticleSystem.h"
#include "ProjectileDrawable.h"

class GameRenderer : public Renderer{
public:

	void render();
	//void render(int dt);
	//sf::Image render();
	void clear();
	void draw();

	void display();
	void drawPlayers();
	void drawProjectiles();
	void drawMap();
	void drawItems();
	void addGame(GameLogic * g);
	void addWindow(sf::RenderWindow * g);
	void handleViews();
	void drawParticleSystems();
	void updateParticleSystems(int dt);
	sf::Texture getLastFrame();

	GameRenderer();
	GameRenderer(sf::RenderWindow* window, GameLogic* game);
	~GameRenderer();
	//void setBoards(Board b1, Board b2);
	
	bool initRenderer();

	sf::RenderWindow* window;
	GameLogic* game;
	sf::Font font;
	sf::Texture lastFrame;//not implemented
	bool texturesLoaded = false;
	const float size = 100.f;
	//sf::CircleShape shape(size);
	sf::CircleShape shape;
	MapDrawable* mapDrawable;
	PlayerDrawable * playerDrawable1;
	PlayerDrawable * playerDrawable2;
	sf::View minimapView;
	sf::View mainView;
	std::vector<ParticleSystem*> _particleSystems;
	void addPlayerAlert(Player *p, std::string text);
	void addPlayerAlert(int playerID, std::string text);
	void setDisplayHitboxes(bool value);
	void setDisplayPositions(bool value);
	void setDisplayFPS(bool value);
	void __showFPS();
	void __showPlayerPositions();
	void playerHitDisplay(float x, float y);
	bool _displayHitboxes;
	bool _displayPositions;
	bool _displayFPS;
};

#endif // !__Game_Renderer__
