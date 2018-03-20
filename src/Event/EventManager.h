#pragma once

//class Event

#include <vector>
#include <SFML\Audio.hpp>
//#include "../Game/GameLogic.h"
#include "../Renderer/GameRenderer.h"
class GameLogic;
enum EventType{NoEvent, ProjectileSpawn, CollisionGeneral, Countdown3, Countdown2, Countdown1, CountdownStart};
class Event {
public:
	Event(EventType et, int id) { type = et; _id = id; };
	Event(EventType et, Entity *e) { type = et; entity = e; };
	EventType type;
	int _id;
	Entity *entity{ nullptr };
	int lifetime = 0;
	bool handled = false;
};
class EventManager
{
public:
	//EventManager();
	//void tick();
	virtual ~EventManager();
	static EventManager& getInstance();
	static void queueEvent(Event e);
	void handleEvents();
	const int DEFAULT_LIFETIME_DEATH = 1000;
	void setGame(GameLogic *g);
	void setRenderer(Renderer *r);
	GameLogic *game;
	Renderer *renderer;
	sf::Sound sound;
	sf::SoundBuffer sbuffer;
private:
	//static EventManager& instance;
	std::vector<Event> _events;
	EventManager();
	bool __handleEvent(Event event);

	void __handleEventProjectileSpawn(Projectile * projectile);

};
