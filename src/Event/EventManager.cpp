#include "EventManager.h"
//#include "../States/StateManager.h"
//#include "../Game/GameLogic.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	_events.clear();
}
/*
EventManager& EventManager::getInstance() {
	static EventManager instance;
	return instance;
}
*/

void EventManager::queueEvent(Event e) {
	_events.push_back(e);
}

void EventManager::handleEvents(int dt)
{

	for (int i = _events.size() - 1; i >= 0; i--) {
		Event &event = _events.at(i);
		event.lifetime += dt;
		if (!event.handled) {
			if (__handleEvent(event)) {
				event.handled = true;
			}
		}
		if (event.lifetime >= DEFAULT_LIFETIME_DEATH) {
			_events.erase(_events.begin() + i);
		}
	}
	printf("Event Queue ---------- : %d\n", _events.size());
}

void EventManager::setGame(GameLogic * g){
	game = g;
}

void EventManager::setRenderer(Renderer * r){
	renderer = r;
}

bool EventManager::__handleEvent(Event event){
	EventType e = event.type;
	//int id = even
	switch (e) {

	/*MenuEvents*/
	case EventType::MenuSelection: {
		audio->queueAudioEvent(AudioEvent::MenuSelectionAudio, nullptr, false);
		break;
	}
	case EventType::MenuSelectionError: {
		audio->queueAudioEvent(AudioEvent::MenuSelectionErrorAudio, nullptr, false);
		break;
	}
	case EventType::MenuReturn: {
		audio->queueAudioEvent(AudioEvent::MenuReturnAudio, nullptr, false);
		break;
	}
	case EventType::MenuItemChange: {
		audio->queueAudioEvent(AudioEvent::MenuItemChangeAudio, nullptr, false);
		break;
	}
	case EventType::MenuItemIncrease: {
		audio->queueAudioEvent(AudioEvent::MenuItemIncreaseAudio, nullptr, false);
		break;
	}
	case EventType::MenuItemDecrease: {
		audio->queueAudioEvent(AudioEvent::MenuItemDecreaseAudio, nullptr, false);
		break;
	}
	/*Game Events*/
	case EventType::ProjectileSpawn: {
		//Entity *e = game->findEntity(id);

		Projectile* p = dynamic_cast<Projectile*>(event.entity);
		__handleEventProjectileSpawn(p);
		printf("Event, PROJECTILE SPAWN -- PROJECTILE SPAWN -- PROJECTILE SPAWN!!!\n : ID: %d", event._id);
		break;
		}
	case EventType::Countdown1:
	case EventType::Countdown2:
	case EventType::Countdown3: {
		__handleEventCoundownTick();
		break;
	}
	case EventType::CountdownStart: {
		__handleEventCoundownStart();
		break;
	}


	case EventType::PlayerShotChargeStart: {
		audio->queueAudioEvent(AudioEvent::AudioShotCharge, event.entity, true);
		break;
	}
	case EventType::PlayerShotChargeStartMid: {
		audio->stopAudioEvent(AudioEvent::AudioShotCharge, event.entity);
		if (!audio->hasAudioEvent(AudioEvent::AudioShotChargeMid, event.entity)) {
			audio->queueAudioEvent(AudioEvent::AudioShotChargeMid, event.entity, true);
		}
		break;
	}
	case EventType::PlayerShotChargeStartMax: {
		audio->stopAudioEvent(AudioEvent::AudioShotCharge, event.entity);
		audio->stopAudioEvent(AudioEvent::AudioShotChargeMid, event.entity);
		if (!audio->hasAudioEvent(AudioEvent::AudioShotChargeMax, event.entity)) {
			audio->queueAudioEvent(AudioEvent::AudioShotChargeMax, event.entity, true);
		}
		break;
	}
	case EventType::PlayerShotChargeEnd: {
		audio->stopAudioEvent(AudioEvent::AudioShotCharge, event.entity);
		audio->stopAudioEvent(AudioEvent::AudioShotChargeMid, event.entity);
		audio->stopAudioEvent(AudioEvent::AudioShotChargeMax, event.entity);
		break;
	}
	case EventType::PlayerHit: {
		GameRenderer* gr{ dynamic_cast<GameRenderer*>(renderer) };
		if (gr != nullptr) {
			gr->playerHitDisplay(event.entity->posX, event.entity->posY);
		}
		audio->queueAudioEvent(AudioEvent::PlayerHurtAudio, event.entity, false);
		break;
	}

	case EventType::PlayerPickupEnergy:
	case EventType::PlayerPickupPowerUp:
	case EventType::PlayerPickup: {
		GameRenderer* gr{ dynamic_cast<GameRenderer*>(renderer) };
		if (gr != nullptr) {
			gr->playerHitDisplay(event.entity->posX, event.entity->posY);
		}
		audio->queueAudioEvent(AudioEvent::PlayerPickupAudio, event.entity, false);

		break;
	}
	case EventType::PlayerLowHP: {
		
		break;
	}


	case EventType::NoEvent:
	default: {	
		printf("Event, NOEVENT!!!\n : ID: %d", event._id);
		break;
		}
	}
	return true;
}

void EventManager::__handleEventProjectileSpawn(Projectile* projectile) {

	audio->queueAudioEvent(AudioEvent::ProjectileSpawnAudio, projectile, false);
}

void EventManager::__handleEventCoundownStart()
{
	audio->queueAudioEvent(AudioEvent::AudioCountdownTick, nullptr, false);
}

void EventManager::__handleEventCoundownTick()
{
	audio->queueAudioEvent(AudioEvent::AudioCountdownStart, nullptr, false);
}


void EventManager::setAudioEventManager(AudioEventManager *aem) {
	audio = aem;
}