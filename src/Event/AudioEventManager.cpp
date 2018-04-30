
#include "AudioEventManager.h"
#include "../Game/Entity.h"

AudioEventManager::AudioEventManager() {
	_initSoundBuffers() ;
} 

AudioEventManager::~AudioEventManager() {
	for (int i = _sounds.size() - 1; i >= 0; --i) {
		if (_sounds.at(i) != nullptr) {
			delete _sounds.at(i);
		}
	}
	_sounds.clear();
	_soundBufferMap.clear();
	_repeatIntervalMap.clear();
	//_soundsOnRepeat.clear();
} 

bool AudioEventManager::_initSoundBuffers() {
	sf::SoundBuffer buffer;
	bool success = true;
	for (int i = 0; i < SOUNDS_COUNT; i++) {
		__sounds[i] = AudioEventSound();
		__sounds[i].stop();
	}

	/*
	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/countdown.wav"))
	success = false;
	_soundBufferMap[AudioEvent::AudioCountdownTick] = buffer;
	*/

	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/countdown.wav"))
		success = false;
	_soundBufferMap[AudioEvent::AudioCountdownTick] = buffer;
	
	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/go.wav"))
		success = false;
	_soundBufferMap[AudioEvent::AudioCountdownStart] = buffer;


	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/song019.wav"))
		success = false;
	_soundBufferMap[AudioEvent::DefaultEventAudio] = buffer;

	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/song105.wav"))
		success = false;
	_soundBufferMap[AudioEvent::TestEventAudio] = buffer;

	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/song170.wav"))
		success = false;
	_soundBufferMap[AudioEvent::AudioShotCharge] = buffer;

	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/song171.wav"))
		success = false;
	_soundBufferMap[AudioEvent::AudioShotChargeLow] = buffer;

	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/song172.wav"))
		success = false;
	_soundBufferMap[AudioEvent::AudioShotChargeMid] = buffer;
	
	buffer = sf::SoundBuffer();
	if (!buffer.loadFromFile("./Assets/Sounds/song173.wav"))
		success = false;
	_soundBufferMap[AudioEvent::AudioShotChargeMax] = buffer;



	/*Defining the repeat interval of persistant sounds*/
	_repeatIntervalMap[AudioEvent::AudioShotCharge] = 200;
	_repeatIntervalMap[AudioEvent::AudioShotChargeLow] = 150;
	_repeatIntervalMap[AudioEvent::AudioShotChargeMid] = 125;
	_repeatIntervalMap[AudioEvent::AudioShotChargeMax] = 100;
	return true;
} 
void AudioEventManager::queueAudioEvent(AudioEvent event, Entity *e, bool repeat) {

	try {
		sf::SoundBuffer& buffer{ _soundBufferMap[event] };
		AudioEventSound *aes{ new AudioEventSound(buffer, e) };
		aes->m_event = event;
		if (repeat) {
			aes->_m_repeat = true;
			aes->setLoop(true);
			if (_repeatIntervalMap.find(event) != _repeatIntervalMap.end()) {
				int repeatInt = _repeatIntervalMap[event];
				aes->repeatInterval = repeatInt;
			}
			else {
				//The map doesnt have a repeat interval, use default
				aes->repeatInterval = aes->lifetime;
			}
		}
		else {
			aes->_m_repeat = false;
		}
		
		aes->play();
		_sounds.push_back(aes);
	}
	catch (const std::out_of_range& oor) {
		printf("cannot find the sound for this event...,\n");
	}
	
	for (int i = 0; i < SOUNDS_COUNT; i++) {
		if (__sounds[i].getStatus() != sf::SoundSource::Status::Playing) {
			try {
				__sounds[i].stop();
				sf::SoundBuffer& bf{ _soundBufferMap[event] };
				__sounds[i] = AudioEventSound(bf, e);
				__sounds[i].m_entity_ptr = e;
				__sounds[i]._m_repeat = repeat;
				__sounds[i].lifetime = 1000;
				__sounds[i].m_event = event;
				//__sounds[i].play();
			}
			catch (const std::out_of_range& oor) {
				printf("cannot find the sound for this event...,\n");
			}
		}
	}

} 

void AudioEventManager::stopAudioEvent(AudioEvent event, Entity *e){
 	for (int i = _sounds.size() - 1; i >= 0; --i) {
		AudioEventSound *aes{ _sounds.at(i) };
		if (e == nullptr) {
			if (aes->m_event == event) {
				aes->setLoop(false);
				aes->stop();
			}
		}
		else {
			if (e == aes->m_entity_ptr) {
				if (aes->m_event == event) {
					aes->setLoop(false);
					aes->stop();
				}
			}
		}
	}
	//std::for_each(_sounds, nullptr);
}
bool AudioEventManager::hasAudioEvent(AudioEvent event, Entity * e)
{
	bool found = false;
	AudioEventSound *foundAudio{ nullptr };
	for (int i = _sounds.size() - 1; i >= 0; --i) {
		AudioEventSound *aes{ _sounds.at(i) };
		if (e == nullptr) {
			if (aes->m_event == event) {
				found = true;
			}
		}
		else {
			if (e == aes->m_entity_ptr) {
				if (aes->m_event == event) {
					found = true;
				}
			}
		}
	}
	return found;
}
void AudioEventManager::stopAllAudioEvents(){
	for (int i = _sounds.size() - 1; i >= 0; --i) {
		AudioEventSound *aes{ _sounds.at(i) };
		aes->stop();
		if (aes != nullptr) {
			delete aes;
		}
	}
	_sounds.clear();

	for (int i = 0; i < SOUNDS_COUNT; i++) {
		__sounds[i].stop();
	}
}

void AudioEventManager::handleEvents( int dt ) {

	bool to_remove = false;
	for (int i = _sounds.size()-1; i >=0; --i) {
		to_remove = false;
		try {
			/**/
			AudioEventSound* sound{ _sounds.at(i) };
			bool loop = sound->getLoop();

			sound->lifetime -= dt;
			if (sound->getLoop()) {
				sound->tickUntilRepeat += dt;
				if (sound->tickUntilRepeat >= sound->repeatInterval) {
					sound->setPlayingOffset(sf::Time());
					sound->tickUntilRepeat -= sound->repeatInterval;
				}
			}
			
			if (sound->getStatus() != sf::SoundSource::Status::Playing) {
					to_remove = true;
			}
			if (sound->lifetime < 0) {
				to_remove = true;
			}

			if (to_remove) {
				sound->stop();
				delete sound;
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
		if (__sounds[i].lifetime < 0) {
			__sounds[i].stop();
		}
	}
		
} 

AudioEventSound::AudioEventSound():
	AudioEventSound(nullptr){
}

AudioEventSound::AudioEventSound(sf::SoundBuffer & buffer):
	AudioEventSound(buffer, nullptr){
}

AudioEventSound::AudioEventSound(Entity * e):
	sf::Sound(),
	m_entity_ptr(e){
}

AudioEventSound::AudioEventSound(sf::SoundBuffer & buffer, Entity * e):
	sf::Sound(buffer),
	m_entity_ptr(e){
}
