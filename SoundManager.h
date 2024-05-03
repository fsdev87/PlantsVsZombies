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
	int capacity = 10;

public:
	SoundManager() {
		this->names = new string[capacity];
		this->buffers = new SoundBuffer[capacity];
		this->sounds = new Sound[capacity];
		this->count = 0;
	}

	void resize(int n) {
		SoundBuffer* buffertemp = new SoundBuffer[capacity];
		Sound* soundtemp = new Sound[capacity];
		for (int i = 0; i < capacity; i++) {
			buffertemp[i] = this->buffers[i];
			soundtemp[i] = this->sounds[i];
		}
		delete[] this->sounds;
		delete[] this->buffers;
		this->buffers = buffertemp;
		this->sounds = soundtemp;
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
};
