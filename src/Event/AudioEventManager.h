/*
Developped by PlasmaLotus
*/

#ifndef __AUDIO_EVENT_MANAGER__
#define __AUDIO_EVENT_MANAGER__
#include <SFML/Audio.hpp>
#include <map>

enum AudioEvent {NoEventAudio, DefaultEventAudio, TestEventAudio, MenuItemIncreaseAudio, MenuItemDecreaseAudio, MenuSelectionAudio, MenuSelectionErrorAudio, MenuItemChangeAudio, MenuReturnAudio, AudioCountdownStart, AudioCountdownTick, 
	ProjectileSpawnAudio, AudioShotCharge, AudioShotChargeLow, AudioShotChargeMid, AudioShotChargeMax, PlayerHurtAudio, PlayerPickupAudio, PlayerPickupPowerupAudio, PlayerPickupEnergyAudio} ;
class Entity;

class AudioEventSound : public sf::Sound {
public:
	AudioEventSound();
	AudioEventSound(sf::SoundBuffer &buffer);
	AudioEventSound(Entity* e);
	AudioEventSound(sf::SoundBuffer &buffer, Entity* e);
	Entity * m_entity_ptr;
	bool _m_repeat = false;
	int lifetime = 20000;
	int repeatInterval = 0;
	int tickUntilRepeat = 0;
	AudioEvent m_event;
};

class AudioEventManager {
public:
	AudioEventManager();
	~AudioEventManager();

	void queueAudioEvent(AudioEvent event, Entity *e = nullptr, bool repeat = false);
	void stopAudioEvent(AudioEvent event, Entity *e = nullptr);
	bool hasAudioEvent(AudioEvent event, Entity *e = nullptr);
	void stopAllAudioEvents();
	void handleEvents(int dt);

private:
	static const int SOUNDS_COUNT{ 16 };
	std::map<AudioEvent, sf::SoundBuffer> _soundBufferMap;
	std::map<AudioEvent, int> _repeatIntervalMap;
	std::vector<AudioEventSound*> _sounds;
	AudioEventSound __sounds[SOUNDS_COUNT];
	bool _initSoundBuffers();
};

#endif // AUDIO EVENT MANAGER
