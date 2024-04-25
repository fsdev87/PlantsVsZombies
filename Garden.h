#pragma once

struct {
	const int leftX = 255;
	const int rightX = 975;
	const int topY = 80;
	const int bottomY = 560;

	bool valid(int x, int y) const {
		if (x >= leftX && x <= rightX && y >= topY && y <= bottomY) {
			return true;
		}
		return false;
	}
} gardenCords;