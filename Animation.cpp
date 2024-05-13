#include "Animation.h"

int Animation::getColumns() { return this->columns; }

void Animation::setColumns(int cols) { this->columns = cols; }

int Animation::getFrame() { return this->frame; }

void Animation::setDelay(float d) { this->delay = d; }

Animation::Animation(int boxX, int boxY, int cols) : boxX(boxX), boxY(boxY), columns(cols), frame(0) {
	this->animClock.restart();
}

void Animation::animate(Sprite& sprite) {
	float time = animClock.getElapsedTime().asMilliseconds();
	if (time > this->delay) {
		sprite.setTextureRect(IntRect(this->frame * this->boxX, 0, this->boxX, this->boxY));
		this->frame += 1;
		this->animClock.restart();
	}
	if (this->frame >= this->columns) this->frame = 0;
}

void Animation::saveEverything(ofstream& file) {
	file.write(reinterpret_cast<char*>(&frame), sizeof(int));
	file.write(reinterpret_cast<char*>(&columns), sizeof(int));
	file.write(reinterpret_cast<char*>(&delay), sizeof(float));
}

void Animation::readEverything(ifstream& file) {
	file.read(reinterpret_cast<char*>(&frame), sizeof(int));
	file.read(reinterpret_cast<char*>(&columns), sizeof(int));
	file.read(reinterpret_cast<char*>(&delay), sizeof(float));
}

void Animation::setFrame(int f) { this->frame = f; this->animClock.restart(); }
