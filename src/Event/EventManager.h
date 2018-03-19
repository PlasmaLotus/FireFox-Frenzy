#pragma once

//class Event

#include <vector>
//#include "../Game/GameLogic.h"
#include "../Renderer/GameRenderer.h"
class GameLogic;
enum EventType{NoEvent};
class Event {
public:
	Event(EventType et, int id) { type = et; _id = id; };
	EventType type;
	int _id;
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
private:
	//static EventManager& instance;
	std::vector<Event> _events;
	EventManager();
	void __handleEvent(EventType e, int id);

};
