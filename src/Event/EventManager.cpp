#include "EventManager.h"
#include "../States/StateManager.h"
//#include "../Game/GameLogic.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	_events.clear();
}

EventManager& EventManager::getInstance() {
	static EventManager instance;
	return instance;
}


void EventManager::queueEvent(Event e) {
	getInstance()._events.push_back(e);
}

void EventManager::handleEvents()
{
	int dt = StateManager::getInstance().getElapsedTime();
	/*
	for (std::vector<Event>::iterator i = _events.begin(); i != _events.end(); i++) {
		i->lifetime += dt;
		if (!i->handled) {
			__handleEvent(i->type, i->_id);
			i->handled = true;
		}
		if (i->lifetime >= DEFAULT_LIFETIME_DEATH) {
			_events.erase(i);
		}
	}
	*/

	for (int i = _events.size() - 1; i >= 0; i--) {
		Event &event = _events.at(i);
		event.lifetime += dt;
		if (!event.handled) {
			__handleEvent(event.type, event._id);
			event.handled = true;
		}
		if (event.lifetime >= DEFAULT_LIFETIME_DEATH) {
			_events.erase(_events.begin() + i);
		}
	}
}

void EventManager::setGame(GameLogic * g)
{
	game = g;
}

void EventManager::setRenderer(Renderer * r)
{
	renderer = r;
}

void EventManager::__handleEvent(EventType e, int id){
	printf("Event, NOEVENT!!!\n : ID: %d", id);
}