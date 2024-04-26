#pragma once
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
			if (names[i] == n) return i;
		}
		return -1;
	}

	void resize(int resizeBy) {
		Texture* tempTextures = new Texture[capacity + resizeBy];
		string* tempNames = new string[capacity + resizeBy];

		for (int i = 0; i < idx; i++) {
			tempTextures[i] = textures[i];
			tempNames[i] = names[i];
		}

		delete[] textures;
		delete[] names;

		textures = tempTextures;
		names = tempNames;

		capacity += resizeBy;
	}


public:
	TextureManager(int t = 10) : capacity(t), idx(0) {
		textures = new Texture[capacity];
		names = new string[capacity];
	};

	void addTexture(string source, string n) {
		if (idx >= capacity) resize(10);
		Texture temp;
		if (!temp.loadFromFile(source)) {
			cout << "Couldn't load " << n << " texture from " << source << endl;
		}
		textures[idx] = temp;
		names[idx] = n;
		idx++;
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
		return dummyTexture;
	}

	~TextureManager() {
		delete[] textures;
		textures = nullptr;
	}
};


void loadTextures(TextureManager* TM) {
	TM->addTexture("assets/Screens/ChooserBackground.png", "inventory"); // Inventory Background

	TM->addTexture("assets/Background/bgday.jpg", "bgday");
	TM->addTexture("assets/Background/bgnight.jpg", "bgnight");
	TM->addTexture("assets/Background/limitedbg.jpg", "limitedbg");
	TM->addTexture("assets/Background/waterday.jpg", "waterday");
	TM->addTexture("assets/Background/waternight.jpg", "waternight");

	//->All Inventory Cards
	TM->addTexture("assets/Screens/Cards/card_sunflower.png", "card-sunflower");
	TM->addTexture("assets/Screens/Cards/card_peashooter.png", "card-peashooter");
	TM->addTexture("assets/Screens/Cards/card_repeaterpea.png", "card-repeater");
	TM->addTexture("assets/Screens/Cards/card_wallnut.png", "card-wallnut");
	TM->addTexture("assets/Screens/Cards/card_snowpea.png", "card-snowpea");
	TM->addTexture("assets/Screens/Cards/card_cherrybomb.png", "card-cherrybomb");
	TM->addTexture("assets/Screens/Cards/card_chomper.png", "card-chomper");

	//TM->addTexture("assets/Spritesheets/shovel.png", "shovel");
	// Spritesheets
	TM->addTexture("assets/Spritesheets/peashooter.png", "spritesheet-peashooter");
	TM->addTexture("assets/Spritesheets/wallnut.png", "spritesheet-wallnut");
	TM->addTexture("assets/Spritesheets/cherrybomb.png", "spritesheet-cherrybomb");
	TM->addTexture("assets/Spritesheets/repeater.png", "spritesheet-repeater");
	TM->addTexture("assets/Spritesheets/snowpea.png", "spritesheet-snowpea");
	TM->addTexture("assets/Spritesheets/sunflower.png", "spritesheet-sunflower");
	TM->addTexture("assets/Spritesheets/sun.png", "spritesheet-sun");
	TM->addTexture("assets/Spritesheets/nZombEat.png", "spritesheet-normalZEat");
	TM->addTexture("assets/Spritesheets/nZombWalk.png", "spritesheet-normalZWalk");
	TM->addTexture("assets/Spritesheets/bucHeadZombEat.png", "spritesheet-bucketZEat");
	TM->addTexture("assets/Spritesheets/bucHeadZombWalk.png", "spritesheet-bucketZWalk");
	TM->addTexture("assets/Spritesheets/zombdie.png", "spritesheet-zombieDeath");

	TM->addTexture("assets/Bullets/peabullet.png", "bullet");
	TM->addTexture("assets/Bullets/peabulletexplode.png", "bulletExplode");
	TM->addTexture("assets/Bullets/peaice.png", "bulletIce");

}