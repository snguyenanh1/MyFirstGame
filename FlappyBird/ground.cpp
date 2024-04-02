#include "ground.h"

Ground::Ground() {
	groundTexture = nullptr;
	groundRect = { 0, SCREEN_HEIGHT - GROUND_HEIGHT, GROUND_WIDTH, GROUND_HEIGHT };
	scrollSpeed = 2;
}

Ground::~Ground() {
	freeGround();
}

bool Ground::loadGround(SDL_Renderer* renderer, const char* path) {
	groundTexture = new Texture();
	if (!groundTexture->loadTexture(renderer, path)) {
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
	groundTexture->renderTexture(renderer, groundRect.x, groundRect.y);
	if (groundRect.x <= 0) {
		groundTexture->renderTexture(renderer, groundRect.x + GROUND_WIDTH, groundRect.y);
	}
}

void Ground::freeGround() {
	groundTexture->freeTexture();
}
