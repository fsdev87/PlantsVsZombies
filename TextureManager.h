#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;


class TextureManager {
private:
	// For variables
	Texture* textures;
	string* names;
	int capacity;
	int idx;
	Texture dummyTexture;

private:
	// For functions
	int getIndexFromName(string n) {
		for (int i = 0; i < idx; i++) {
			if (this->names[i] == n) return i;
		}
		return -1;
	}

	void resize(int resizeBy) {
		Texture* tempTextures = new Texture[capacity + resizeBy];
		string* tempNames = new string[capacity + resizeBy];

		for (int i = 0; i < idx; i++) {
			tempTextures[i] = this->textures[i];
			tempNames[i] = this->names[i];
		}

		delete[] textures;
		delete[] names;

		this->textures = tempTextures;
		this->names = tempNames;

		this->capacity += resizeBy;
	}


public:
	TextureManager(int t = 10) : capacity(t), idx(0) {
		this->textures = new Texture[capacity];
		this->names = new string[capacity];
	};

	void addTexture(string source, string n) {
		if (idx >= capacity) resize(10);
		Texture temp;
		if (!temp.loadFromFile(source)) {
			cout << "Couldn't load " << n << " texture from " << source << endl;
		}
		this->textures[idx] = temp;
		this->names[idx] = n;
		this->idx++;
	}

	Texture& operator[](string n) {
		int index = getIndexFromName(n);
		if (index != -1) return textures[index];
		return dummyTexture;
	}

	Texture& getTexture(int n) {
		if (n < idx)
			return textures[n];
		return dummyTexture;
	}

	Texture& getTexture(string name) {
		int index = getIndexFromName(name);
		if (index != -1)
			return textures[index];
		return this->dummyTexture;
	}

	~TextureManager() {
		delete[] this->textures;
		this->textures = nullptr;
	}
};





#endif