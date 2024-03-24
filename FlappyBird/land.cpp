#include "land.h"


void Land::init() {
	loadTexture("assets/image/land.png");
	scrollSpeed = 2;
	destRect = {0, SCREEN_HEIGHT - LAND_HEIGHT, LAND_WIDTH, LAND_HEIGHT};
}

Land::~Land() {
	freeTexture();
}

void Land::updateLand() {
	destRect.x -= scrollSpeed;
	if (destRect.x <= -LAND_WIDTH) {
		destRect.x = 0;
	}
}

void Land::renderLand() {
	renderTexture(destRect.x, destRect.y, &destRect);
	if (destRect.x <= SCREEN_WIDTH - LAND_WIDTH) {
		renderTexture(destRect.x + LAND_WIDTH, destRect.y, &destRect);
	}
}