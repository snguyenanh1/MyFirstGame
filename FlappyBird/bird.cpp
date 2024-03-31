#include "bird.h"
#include <algorithm>

Bird::Bird() {
	birdPosition.setPosition(SCREEN_WIDTH/9, SCREEN_HEIGHT/2);
	isFlapping = false;
	isFlappingUp = false;
	speed = 0;
	frameCounter = 0;
}

bool Bird::loadBird(SDL_Renderer* renderer) {
	int idx = rand() % 3;
	for (int i = 0; i < 3; i++) {
		Texture* birdTexture = new Texture();
		if (!birdTexture->loadTexture(renderer, paths[idx][i].c_str())) {
			return false;
		}
		birdTextures.push_back(birdTexture);
	}
	return true;
}

void Bird::updateBird() {
	if (isFlapping) {
		speed = flapSpeed;
		isFlapping = false;
		isFlappingUp = true;
	} 
	else {
		speed += gravity;
	}

	if (speed > maxSpeed) {
		speed = maxSpeed;
	}

	birdPosition.y += (int) speed;

	if (birdPosition.y < 0) {
		birdPosition.y = 0;
		speed = 0;
		angle = 0;
	}

	if (birdPosition.y + birdTextures[0]->getTextureHeight() > SCREEN_HEIGHT - 140) {
		birdPosition.y = SCREEN_HEIGHT - 140 - birdTextures[0]->getTextureHeight(); 
		speed = 0;
		angle = 0;
	}

	if (isFlappingUp) {
		angle = -maxAngle;
	} 
	else {
		angle = std::min(maxAngle, speed*7);		
	}
		

	if (speed >= 0) {
		isFlappingUp = false;
	}

	frameCounter++;
	if (frameCounter >= framePerChange) {
		currentFrame = (currentFrame + 1) % 3;
		frameCounter = 0;
	}
	
}

void Bird::renderBird(SDL_Renderer* renderer) {
	birdTextures[currentFrame]->renderTexture(renderer, birdPosition.x, birdPosition.y, nullptr, angle);
}

void Bird::freeBird() {
	for (int i = 0; i < 3; i++) {
		birdTextures[i]->freeTexture();
	}	
}

void Bird::flap() {
	isFlapping = true;
}

Bird::~Bird() {
	freeBird();
}

int Bird::getWidth() {
    return birdTextures[0]->getTextureWidth();
}

int Bird::getHeight() {
    return birdTextures[0]->getTextureHeight();
}

Position Bird::getPosition() {
    return birdPosition;
}
