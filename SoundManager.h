#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;


class SoundManager {
	Music mainMusic;

	string* names;
	SoundBuffer* buffers;
	Sound* sounds;

	int count;
	int capacity = 30;
	void loadSounds() {
		this->loadSound("assets/sounds/menu/mainmusic.mp3", "mainmusic");
		this->loadSound("assets/sounds/plant/cherrybomb.ogg", "cherrybomb-explosion");
		this->loadSound("assets/sounds/zombie/zombiefall.ogg", "zombie-fall");
		this->loadSound("assets/sounds/menu/sunclick.mp3", "sunclick");
		this->loadSound("assets/sounds/menu/misclick.mp3", "misclick");
		this->loadSound("assets/sounds/zombie/lowgroan.ogg", "groan1");
		this->loadSound("assets/sounds/zombie/lowgroan2.ogg", "groan2");
		this->loadSound("assets/sounds/zombie/eating.mp3", "eating");
		this->loadSound("assets/sounds/menu/round1.mp3", "round1");
		this->loadSound("assets/sounds/zombie/mczombie.mp3", "mczombie");
		this->loadSound("assets/sounds/menu/place1.mp3", "place1");
		this->loadSound("assets/sounds/menu/place2.mp3", "place2");
		this->loadSound("assets/sounds/zombie/zombieattack.mp3", "zombieattack");
		this->loadSound("assets/sounds/zombie/zombieroar.mp3", "zombieroar");
		this->loadSound("assets/sounds/zombie/hit.mp3", "hit");
		this->loadSound("assets/sounds/menu/enter.mp3", "enter");
		this->loadSound("assets/sounds/menu/change.mp3", "change");
		this->loadSound("assets/sounds/menu/gameoversound.mp3", "gameover");
		this->loadSound("assets/sounds/menu/28dayslater.mp3", "28dayslater");
		this->loadSound("assets/sounds/menu/last.mp3", "last");
		this->loadSound("assets/sounds/menu/won.mp3", "won");

		this->getSound("last")->setPlayingOffset(sf::seconds(8));
		this->getSound("enter")->setVolume(40);
		this->getSound("change")->setVolume(40);
		this->getSound("won")->setVolume(20);
		this->getSound("eating")->setVolume(40);
		this->getSound("hit")->setVolume(70); this->getSound("hit")->setPlayingOffset(Time(seconds(0.5)));
		this->getSound("sunclick")->setVolume(50);
		this->getSound("round1")->setVolume(10.0f);
		this->getSound("round1")->setPlayingOffset(Time(seconds(1.05)));

	}
public:
	SoundManager() {
		this->names = new string[capacity];
		this->buffers = new SoundBuffer[capacity];
		this->sounds = new Sound[capacity];
		this->count = 0;

		loadSounds();
	}


	void resize(int n) {
		cout << "resizing by " << n << endl;
		SoundBuffer* buffertemp = new SoundBuffer[capacity + n];
		Sound* soundtemp = new Sound[capacity + n];
		string* nametemp = new string[capacity + n];

		for (int i = 0; i < capacity; i++) {
			buffertemp[i] = this->buffers[i];
			soundtemp[i] = this->sounds[i];
			nametemp[i] = this->names[i];
		}

		delete[] this->sounds;
		delete[] this->buffers;
		delete[] this->names;

		this->buffers = buffertemp;
		this->sounds = soundtemp;
		this->names = nametemp;

		this->capacity += n;
	}

	void loadSound(string source, string name) {
		if (this->count >= this->capacity) this->resize(5);
		if (name == "mainmusic") {
			this->mainMusic.openFromFile(source);
			return;
		}

		if (!this->buffers[this->count].loadFromFile(source)) cout << "Couldn't load from " << source << endl;

		this->sounds[this->count].setBuffer(this->buffers[this->count]);
		this->names[this->count] = name;
		this->count++;
	}

	Music* getMainMusic() {
		return &mainMusic;
	}

	Sound* getSound(string n) {
		for (int i = 0; i < this->count; i++) {
			if (this->names[i] == n) return &this->sounds[i];
		}
		return nullptr;
	}

	Sound* operator[](string n) {
		return this->getSound(n);
	}

	int getSoundIndex(string n) {
		for (int i = 0; i < this->count; i++) {
			if (this->names[i] == n) return i;
		}
		return -1;
	}

	void playSound(string n, int i = -1) {
		if (i != -1) {
			this->sounds[i].play();
		}
		else {
			int index = this->getSoundIndex(n);
			if (index != -1) {
				this->sounds[index].play();
			}
		}
	}

	void stopSound(string n, int i = -1) {
		if (i != -1) {
			this->sounds[i].stop();
		}
		else {
			int index = this->getSoundIndex(n);
			if (index != -1) {
				this->sounds[index].stop();
			}
		}
	}

	~SoundManager() {
		delete[] names;
		delete[] buffers;
		delete[] sounds;
	}
};
