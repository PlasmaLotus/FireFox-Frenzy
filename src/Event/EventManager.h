#ifndef __EventManager__
#define __EventManager__

#include <vector>
#include "../Renderer/GameRenderer.h"
#include "../Game/GameLogic.h"
#include "AudioEventManager.h"
enum EventType{NoEvent, GameStart, GameEnd, ProjectileSpawn, CollisionGeneral, Countdown3, Countdown2, Countdown1, CountdownStart, 
	GainAmmo, LoseAmmo, ShieldHit, OutOfAmmo, TimeLimit, LastManStanding, ShieldOn, ShieldOff,
MenuItemIncrease, MenuItemDecrease, MenuSelection, MenuSelectionError, MenuItemChange, MenuReturn, PauseMenuEnter,
ProjectileSpawnFire, ProjectileSpawnBubble, ProjectileSpawnRapid, ProjectileBubbleBounce,
PlayerLowHP, PlayerShotChargeStart, PlayerShotChargeStartMid, PlayerShotChargeStartMax, PlayerShotChargeEnd,
PlayerHit, PlayerPickup, PlayerPickupEnergy, PlayerPickupPowerUp, PlayerPowerUpLoss
};
class Event {
public:
	Event(EventType et) { type = et;};
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
	EventManager();
	virtual ~EventManager();
	void queueEvent(Event e);
	void handleEvents(int dt);
	const int DEFAULT_LIFETIME_DEATH = 1000;
	void setGame(GameLogic *g);
	void setRenderer(Renderer *r);
	GameLogic *game;
	Renderer *renderer;
	std::vector<Event> _events;
	AudioEventManager *audio;
	void setAudioEventManager(AudioEventManager *aem);
private:
	bool __handleEvent(Event event);
	void __handleEventProjectileSpawn(Projectile * projectile);
	void __handleEventCoundownStart();
	void __handleEventCoundownTick();

};
#endif //__EventManager__