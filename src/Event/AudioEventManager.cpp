
#include "AudioEventManager.h"


AudioEventManager::AudioEventManager() {
	_initSoundBuffers() ;
} 

AudioEventManager::~AudioEventManager() {
	_sounds.clear();
	_soundBufferMap.clear();
	_soundsOnRepeat.clear();
} 

bool AudioEventManager::_initSoundBuffers() {
	sf::SoundBuffer buffer;
	bool success = true;
	if (!buffer.loadFromFile("./Assets/Sounds/ding.flac"))
		success = false;
	_soundBufferMap[AudioEvent::DefaultEventAudio] = buffer;
	
	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/countdown.mp3"))
		success = false;
	
	buffer = sf::SoundBuffer();
	_soundBufferMap[AudioEvent::AudioCountdownTick] = buffer;
	if (!buffer.loadFromFile("./Assets/Sounds/go.mp3"))
		success = false;

	_soundBufferMap[AudioEvent::AudioCountdownStart] = buffer;
	return true;
} 
void AudioEventManager::queueAudioEvent(AudioEvent event, bool repeat = false) {
	/*
	sf::Sound sound;
	try {
		sound.setBuffer(_soundBufferMap[event]);
		_sounds.push_back(sound);
		if (repeat) {
			sf::Sound * s{ &(_sounds.at(_sounds.size() - 1)) };

		}
		_sounds.at(_sounds.size() - 1).play();
	}
	catch (const std::out_of_range& oor) {
		printf("cannot find the sound for this event...,\n");
	}
	*/


	for (int i = 0; i < SOUNDS_COUNT; i++) {
		if (__sounds[i].getStatus() != sf::SoundSource::Status::Playing) {
			__sounds[i].stop();
			__sounds[i].setBuffer(_soundBufferMap[event]);
			__sounds[i].play();
		}
	}

} 

void AudioEventManager::stopAudioEvent(AudioEvent event){

	for (std::map<AudioEvent, sf::Sound*>::iterator it = _soundsOnRepeat.begin(); it != _soundsOnRepeat.end(); ++it) {
		if (it->first == event) {
			it->second->stop();
		}
	}

	for (int i = _soundsOnRepeat.size()-1; i>=0; i--) {
		//sf::SoundBuffer& buffer = _sounds.at(i).getBuffer();
		/*
		if ( buffer == _soundBufferMap.at(event)) {
		}
		*/
	}
} 

void AudioEventManager::handleEvents( int dt ) {

	for (int i = _sounds.size()-1; i >=0; i--) {
		try {
			/**/
			if (_sounds.at(i).getStatus() == sf::SoundSource::Status::Stopped) {
				_sounds.erase(_sounds.begin() + i);
			}
		}
		catch (const std::out_of_range& oor) {
			printf("cannot reach the sound in question...,\n");
		}
	}
	printf("Audio Queue ---------- : %d\n", _sounds.size());
	for (int i = 0; i < SOUNDS_COUNT; i++) {
		if (__sounds[i].getStatus() != sf::SoundSource::Status::Playing) {
			__sounds[i].stop();
		}
	}
		
} 
 