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

class GameRenderer : public Renderer{
public:

	void render();
	//sf::Image render();
	void clear();
	void draw();

	void display();
	void drawPlayers();
	void addGame(GameLogic * g);
	void addWindow(sf::RenderWindow * g);
	sf::Texture getLastFrame();

	GameRenderer();
	GameRenderer(sf::RenderWindow* window, GameLogic* game);
	~GameRenderer();
	//void setBoards(Board b1, Board b2);
	
	bool initRenderer();

	sf::RenderWindow* window;
	GameLogic* game;

	sf::Texture lastFrame;//not implemented
	bool texturesLoaded = false;
	const float size = 100.f;
	//sf::CircleShape shape(size);
	sf::CircleShape shape;
	PlayerDrawable * playerDrawable1;
	PlayerDrawable * playerDrawable2;

};

#endif // !__Game_Renderer__
