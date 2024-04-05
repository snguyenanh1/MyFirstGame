#include "bird.h"

#include <algorithm>

#include "ground.h"

Bird::Bird() {
	birdPosition.setPosition(SCREEN_WIDTH/9, SCREEN_HEIGHT/2 - 70);
	isFlapping = false;
	isFlappingUp = false;
	speed = 0;
	frameCounter = 0;
}

bool Bird::loadBird(SDL_Renderer* renderer, int idx) {
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


}

void Bird::ticks() {
    frameCounter++;
    if (frameCounter >= framePerChange) {
        currentFrame = (currentFrame + 1) % 3;
        frameCounter = 0;
    }
}

void Bird::renderBird(SDL_Renderer* renderer, bool choose) {
	ticks();
    if (!choose) birdTextures[currentFrame]->renderTexture(renderer, birdPosition.x, birdPosition.y, nullptr, angle);
	else birdTextures[currentFrame]->renderTexture(renderer, SCREEN_WIDTH/2 - 17, 250, nullptr, 0);
}

void Bird::freeBird() {
	for (int i = 0; i < 3; i++) {
		birdTextures[i]->freeTexture();
	}
	birdTextures.clear();
}

void Bird::flap() {
	isFlapping = true;
}

Bird::~Bird() {
	freeBird();
}

Position Bird::getPosition() {
    return birdPosition;
}

bool Bird::updateDeadBird() {
    angle = 45;
    if(birdPosition.y < SCREEN_HEIGHT - birdTextures[0]->getTextureHeight() - GROUND_HEIGHT) {
        birdPosition.y += (int) maxSpeed;
		return false;
    }
	return true;
}

void Bird::resetBird() {
    birdPosition.setPosition(SCREEN_WIDTH / 9, SCREEN_HEIGHT / 2 - 70);
    isFlapping = false;
    isFlappingUp = false;
    speed = 0;
    frameCounter = 0;
    angle = 0;
}


