#include "PlantFactory.h"

using namespace std;
using namespace sf;

PlantFactory::PlantFactory(SoundManager* SM, TextureManager* TM) : plantsArrayIndex(0) {
	this->SMptr = SM;
	this->TMptr = TM;
	this->plants = new Plant * [maxPlants] { nullptr };
}



Plant** PlantFactory::getPlants() { return this->plants; }
int PlantFactory::getPlantsArrayIndex() { return this->plantsArrayIndex; }
int& PlantFactory::getPlantsArrayIndexByRef() { return this->plantsArrayIndex; }

// Handle placing of plant from inventory
void PlantFactory::handlePlacing(Inventory* Inv, int gx, int gy, int& sunCount, int round) {
	if (Inv->hasSelectedSomething()) {
		Inv->handlePlacing(gx, gy, plants, plantsArrayIndex, sunCount, round);
	}
}

void PlantFactory::handleFallingSun(int gx, int gy, FallingSun* sun, Text& sunCountText, int& sunCount) {
	if (gx != sun->getPosition()[0]) {
		// not same column
		return;
	}

	if (gy == ((int)(sun->getPosition()[1]))) {
		sunCount += 25;
		sunCountText.setString(to_string(sunCount));
		sun->setExist(false);
		return;
	}

};

// handles clicking of player on sun
void PlantFactory::handleSunClick(int gx, int gy, Text& sunCountText, int& sunCount) {
	for (int i = 0; i < this->plantsArrayIndex; i++) {
		if (this->plants[i]->getExist() && this->plants[i]->getPosition()[0] == gx && this->plants[i]->getPosition()[1] == gy) {
			this->plants[i]->clickSun(sunCount, this->SMptr);
			sunCountText.setString(to_string(sunCount));
		}
	}
}

void PlantFactory::handleWallnutClick(int gx, int gy) {
	for (int i = 0; i < this->plantsArrayIndex; i++) {
		if (this->plants[i]->getExist()) {
			float* plantPos = this->plants[i]->getPosition();
			if (plantPos[0] == gx && plantPos[1] == gy) {
				this->plants[i]->activate(this->TMptr->getTexture("spritesheet-wallnut-rolling"));
			}
		}
	}
};

void PlantFactory::updateEverything(Zombie** zombies, int zombiesArrayIndex) {
	for (int i = 0; i < this->plantsArrayIndex && this->plants[i] != nullptr; i++) {
		if (this->plants[i]->getExist()) {
			this->plants[i]->animate();
			this->plants[i]->generateSun();


			int plantRow = 0;
			float* plantPos = this->plants[i]->getPosition();
			for (int j = 0; j < zombiesArrayIndex; j++) {
				if (zombies[j]->getExist()) {
					float* zombiePos = zombies[j]->getPosition();
					if ((zombiePos[1] == plantPos[1]) && (zombiePos[0] >= plantPos[0] && zombiePos[0] <= 9)) {
						plantRow++;
					}
				}
			}
			if (plantRow > 0) {
				this->plants[i]->shoot(zombies, zombiesArrayIndex);
			}
			else {
				this->plants[i]->restartBulletClock();
			}
			this->plants[i]->moveBullets(zombies, zombiesArrayIndex);
			this->plants[i]->explode(zombies, zombiesArrayIndex, SMptr);

			this->plants[i]->move(zombies, zombiesArrayIndex);
		}
	}
}

void PlantFactory::draw(RenderWindow& window) {
	for (int i = 0; i < plantsArrayIndex; i++) {
		plants[i]->draw(window);
	}
}