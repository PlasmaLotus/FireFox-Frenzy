#pragma once
#include <SFML/Audio.hpp>
#include <map>
enum AudioEvent {NoEventAudio, DefaultEventAudio, AudioCountdownStart, AudioCountdownTick} ;

class AudioEventManager {
public:
	AudioEventManager();
	~AudioEventManager();
	std::map<AudioEvent, sf::SoundBuffer> _soundBufferMap;
	std::vector<sf::Sound> _sounds;
	std::map<AudioEvent, sf::Sound*> _soundsOnRepeat;
	bool _initSoundBuffers();
	void queueAudioEvent(AudioEvent event, bool repeat);
	void stopAudioEvent(AudioEvent event);
	void handleEvents(int dt);
};