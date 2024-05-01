#include "PlantFactory.h"

using namespace std;
using namespace sf;

PlantFactory::PlantFactory() : plantsArrayIndex(0) {
	plants = new Plant * [maxPlants] { nullptr };
}

Plant** PlantFactory::getPlants() { return this->plants; }
int PlantFactory::getPlantsArrayIndex() { return this->plantsArrayIndex; }
int& PlantFactory::getPlantsArrayIndexByRef() { return this->plantsArrayIndex; }

// Handle placing of plant from inventory
void PlantFactory::handlePlacing(Inventory* Inv, int gx, int gy, int& sunCount) {
	if (Inv->hasSelectedSomething()) {
		Inv->handlePlacing(gx, gy, plants, plantsArrayIndex, sunCount);
	}
}

// handles clicking of player on sun
void PlantFactory::handleSunClick(int gx, int gy, Text& sunCountText, int& sunCount) {
	for (int i = 0; i < this->plantsArrayIndex; i++) {
		if (this->plants[i]->getExist() && this->plants[i]->getPosition()[0] == gx && this->plants[i]->getPosition()[1] == gy) {
			this->plants[i]->clickSun(sunCount);
			sunCountText.setString(to_string(sunCount));
		}
	}
}

void PlantFactory::updateEverything(Zombie** zombies, int zombiesArrayIndex) {
	for (int i = 0; i < this->plantsArrayIndex && this->plants[i] != nullptr; i++) {
		if (this->plants[i]->getExist()) {
			this->plants[i]->animate();
			this->plants[i]->generateSun();

			int plantRow = 0;
			for (int j = 0; j < zombiesArrayIndex; j++) {
				if (zombies[j]->getExist() && (zombies[j]->getPosition()[1] == this->plants[i]->getPosition()[1]) && (zombies[j]->getPosition()[0] <= 9)) {
					plantRow++;
				}
			}
			if (plantRow > 0) {
				this->plants[i]->shoot(zombies, zombiesArrayIndex);
			}
			else {
				this->plants[i]->restartBulletClock();
			}
			this->plants[i]->moveBullets(zombies, zombiesArrayIndex);
			this->plants[i]->explode(zombies, zombiesArrayIndex);

		}
	}
}

void PlantFactory::draw(RenderWindow& window) {
	for (int i = 0; i < plantsArrayIndex; i++) {
		plants[i]->draw(window);
	}
}