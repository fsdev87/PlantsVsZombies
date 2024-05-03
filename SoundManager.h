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

public:
	SoundManager() {
		this->names = new string[capacity];
		this->buffers = new SoundBuffer[capacity];
		this->sounds = new Sound[capacity];
		this->count = 0;
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
