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

	void loadTextures() {
		cout << "Loading Textures\n";
		this->addTexture("assets/Screens/ChooserBackground.png", "inventory"); // Inventory Background

		this->addTexture("assets/Background/levelbg.png", "levelbg");

		this->addTexture("assets/Background/bgday.jpg", "bgday");
		this->addTexture("assets/Background/bgnight.jpg", "bgnight");
		this->addTexture("assets/Background/limitedbg.jpg", "limitedbg");
		this->addTexture("assets/Background/waterday.jpg", "waterday");
		this->addTexture("assets/Background/waternight.jpg", "waternight");
		this->addTexture("assets/Screens/MainMenu.png", "mainmenu");
		this->addTexture("assets/Screens/highscorebg.jpg", "highscorebg");
		this->addTexture("assets/Background/row.jpg", "bgfirst");


		this->addTexture("assets/Screens/decoration/DancingZombie.png", "deco-dz");
		this->addTexture("assets/Screens/decoration/FootballZombie.png", "deco-fz");
		this->addTexture("assets/Screens/decoration/Zombie.png", "deco-z");
		this->addTexture("assets/Screens/decoration/Peashooter.png", "deco-p");
		this->addTexture("assets/Screens/decoration/Wallnut.png", "deco-w");
		this->addTexture("assets/Screens/decoration/Repeater.png", "deco-r");

		this->addTexture("assets/Screens/gold.png", "gold");
		this->addTexture("assets/Screens/silver.png", "silver");
		this->addTexture("assets/Screens/bronze.png", "bronze");

		// this->All Inventory Cards
		this->addTexture("assets/Screens/Cards/card_sunflower.png", "card-sunflower");
		this->addTexture("assets/Screens/Cards/card_peashooter.png", "card-peashooter");
		this->addTexture("assets/Screens/Cards/card_repeaterpea.png", "card-repeater");
		this->addTexture("assets/Screens/Cards/card_wallnut.png", "card-wallnut");
		this->addTexture("assets/Screens/Cards/card_snowpea.png", "card-snowpea");
		this->addTexture("assets/Screens/Cards/card_cherrybomb.png", "card-cherrybomb");

		this->addTexture("assets/Screens/Cards/card_sunflower_dim.png", "card-sunflower_dim");
		this->addTexture("assets/Screens/Cards/card_peashooter_dim.png", "card-peashooter_dim");
		this->addTexture("assets/Screens/Cards/card_repeater_dim.png", "card-repeater_dim");
		this->addTexture("assets/Screens/Cards/card_wallnut_dim.png", "card-wallnut_dim");
		this->addTexture("assets/Screens/Cards/card_snowpea_dim.png", "card-snowpea_dim");
		this->addTexture("assets/Screens/Cards/card_cherrybomb_dim.png", "card-cherrybomb_dim");
		this->addTexture("assets/Spritesheets/shovel.png", "shovel");
		this->addTexture("assets/Static/sun.png", "icon-sun");
		//this->Spritesheets
		this->addTexture("assets/Spritesheets/peashooter.png", "spritesheet-peashooter");
		this->addTexture("assets/Spritesheets/wallnut.png", "spritesheet-wallnut");
		this->addTexture("assets/Spritesheets/v.png", "spritesheet-cherrybomb");
		this->addTexture("assets/Spritesheets/repeater.png", "spritesheet-repeater");
		this->addTexture("assets/Spritesheets/snowpea.png", "spritesheet-snowpea");
		this->addTexture("assets/Spritesheets/sunflower.png", "spritesheet-sunflower");
		this->addTexture("assets/Spritesheets/threepeater.png", "spritesheet-threepeater");
		this->addTexture("assets/Spritesheets/lawnmower.png", "spritesheet-lawnmower");
		this->addTexture("assets/Spritesheets/lawnmowerIdle.png", "image-lawnmowerIdle");
		this->addTexture("assets/Spritesheets/wallnut-half.png", "wallnut-half");
		this->addTexture("assets/Spritesheets/wallnut-dead.png", "wallnut-dead");
		// All are for normal zombie
		this->addTexture("assets/Spritesheets/nZombEat.png", "spritesheet-nZombEat");
		this->addTexture("assets/Spritesheets/nZombWalk.png", "spritesheet-nZombWalk");
		this->addTexture("assets/Spritesheets/headlesswalk.png", "spritesheet-headLessWalk");
		this->addTexture("assets/Spritesheets/headlesseat.png", "spritesheet-headLessEat");
		this->addTexture("assets/Spritesheets/normalzombiedie.png", "spritesheet-headLessDeath");
		this->addTexture("assets/Spritesheets/head.png", "spritesheet-head");
		this->addTexture("assets/Spritesheets/zombdie.png", "spritesheet-zombieDeath");

		this->addTexture("assets/Spritesheets/bucHeadZombEat.png", "spritesheet-bucZEat");
		this->addTexture("assets/Spritesheets/bucHeadZombWalk.png", "spritesheet-bucZWalk");

		this->addTexture("assets/Spritesheets/wallnutrolling.png", "spritesheet-wallnut-rolling");
		// For all explosion
		this->addTexture("assets/Spritesheets/zombash.png", "spritesheet-zombieAshes");

		// Bullets
		this->addTexture("assets/Bullets/peabullet.png", "bullet");
		this->addTexture("assets/Bullets/peabulletexplode.png", "bulletExplode");
		this->addTexture("assets/Bullets/peaice.png", "bulletIce");

		// football left textures
		this->addTexture("assets/Spritesheets/football-walk.png", "football-walk");
		this->addTexture("assets/Spritesheets/football-walk-2.png", "football-walk-2");
		this->addTexture("assets/Spritesheets/football-walk-3.png", "football-walk-3");
		this->addTexture("assets/Spritesheets/football-eat.png", "football-eat");
		this->addTexture("assets/Spritesheets/football-eat-2.png", "football-eat-2");
		this->addTexture("assets/Spritesheets/football-eat-3.png", "football-eat-3");
		this->addTexture("assets/Spritesheets/football-die.png", "football-die");

		// football right textures
		this->addTexture("assets/Spritesheets/football-walk-right.png", "football-walk-right");
		this->addTexture("assets/Spritesheets/football-walk-right-2.png", "football-walk-right-2");
		this->addTexture("assets/Spritesheets/football-walk-right-3.png", "football-walk-right-3");
		this->addTexture("assets/Spritesheets/football-eat-right.png", "football-eat-right");
		this->addTexture("assets/Spritesheets/football-eat-right-2.png", "football-eat-right-2");
		this->addTexture("assets/Spritesheets/football-eat-right-3.png", "football-eat-right-3");

		// dancing textures
		this->addTexture("assets/Spritesheets/dancingwalk1.png", "dancing-walk-1");
		this->addTexture("assets/Spritesheets/dancingeat1.png", "dancing-eat-1");
		this->addTexture("assets/Spritesheets/dancinghead.png", "dancing-head");
		this->addTexture("assets/Spritesheets/dancingdie.png", "dancing-die");
		this->addTexture("assets/Spritesheets/dancingwalk2.png", "dancing-walk-2");
		this->addTexture("assets/Spritesheets/dancingeat2.png", "dancing-eat-2");
		this->addTexture("assets/Spritesheets/dancing-1.png", "dancing-1");
		this->addTexture("assets/Spritesheets/dancing-2.png", "dancing-2");
		this->addTexture("assets/Spritesheets/flyingzombie.png", "flying-zombie");

		this->addTexture("assets/Spritesheets/shovel.png", "shovel");

		this->addTexture("assets/Screens/win.png", "win");

	}

public:
	TextureManager(int t = 10) : capacity(t), idx(0) {
		this->textures = new Texture[capacity];
		this->names = new string[capacity];

		loadTextures();
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
		cout << "\nWRONG NAME ENTERED THATS WHY WHITE TEXTURE" << name << "\n";
		return this->dummyTexture;
	}

	~TextureManager() {
		delete[] this->textures;
		this->textures = nullptr;
	}
};





#endif