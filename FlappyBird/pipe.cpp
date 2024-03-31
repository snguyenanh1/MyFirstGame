#include "pipe.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


Pipe::Pipe() {
	topPipeTexture = NULL();
	bottomPipeTexture = NULL();
	topPipePosition.x = SCREEN_WIDTH + 65;
	bottomPipePosition.x = SCREEN_WIDTH + 65;
	randomPipe();
}

Pipe::~Pipe() {
	freePipe();
}

bool Pipe::loadPipe(SDL_Renderer* renderer) {
	topPipeTexture = new Texture();
	bottomPipeTexture = new Texture();
	if (!topPipeTexture->loadTexture(renderer, "assets/pipe/top.png") ||
		!bottomPipeTexture->loadTexture(renderer, "assets/pipe/bottom.png"))
		return false;
	return true;
}

void Pipe::randomPipe() {
	topPipePosition.y = MIN_HEIGHT + rand() % (MAX_HEIGHT - MIN_HEIGHT + 1);
	bottomPipePosition.y = PIPE_HEIGHT - topPipePosition.y + PIPE_GAP;
}

void Pipe::updatePipe() {
		topPipePosition.x -= PIPE_SPEED;
		bottomPipePosition.x -= PIPE_SPEED;
}

bool Pipe::isOffScreen() {
	return topPipePosition.x + PIPE_WIDTH < 0;
}

void Pipe::renderPipe(SDL_Renderer* renderer) {
	topPipeTexture->renderTexture(renderer, topPipePosition.x, 0 - topPipePosition.y);
	bottomPipeTexture->renderTexture(renderer, bottomPipePosition.x, bottomPipePosition.y);
}

void Pipe::freePipe() {
	if (topPipeTexture != nullptr) {
		topPipeTexture->freeTexture();
		delete topPipeTexture;
	}
	if (bottomPipeTexture != nullptr) {
		bottomPipeTexture->freeTexture();
		delete bottomPipeTexture;
	}
}

Position Pipe::getTopPipePosition() {
    return topPipePosition;
}

Position Pipe::getBottomPipePosition() {
    return bottomPipePosition;
}

int Pipe::getPipeWidth() {
    return PIPE_WIDTH;
}

int Pipe::getPipeHeight() {
    return PIPE_HEIGHT;
}
