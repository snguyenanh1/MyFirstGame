#include "ground.h"


Ground::Ground() {
	groundRect = { 0, SCREEN_HEIGHT - GROUND_HEIGHT, GROUND_WIDTH, GROUND_HEIGHT };
	scrollSpeed = 2;
}

Ground::~Ground() {
	freeGround();
}

bool Ground::loadGround(SDL_Renderer* renderer, const char* path) {
	if (loadTexture(renderer, path)) {
		return false;
	}
	return true;
}

void Ground::updateGround() {
	groundRect.x -= scrollSpeed;
	if (groundRect.x <= -GROUND_WIDTH) {
		groundRect.x = 0;
	}
}

void Ground::renderGround(SDL_Renderer* renderer) {
	renderTexture(renderer, groundRect.x, groundRect.y);
	if (groundRect.x <= 0) {
		renderTexture(renderer, groundRect.x + GROUND_WIDTH, groundRect.y);
	}
}

void Ground::freeGround() {
	freeTexture();
}