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
	topPipePosition.y = minHeight + rand() % (maxHeight - minHeight + 1);
	bottomPipePosition.y = pipeHeight - topPipePosition.y + pipeGap;
}

void Pipe::updatePipe() {
		topPipePosition.x -= pipeSpeed;
		bottomPipePosition.x -= pipeSpeed;
}

bool Pipe::isOffScreen() {
	return topPipePosition.x + pipeWidth < 0;
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
