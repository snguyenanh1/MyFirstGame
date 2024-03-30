#include "pipe.h"
#include <cstdlib>
#include <ctime>


Pipe::Pipe() {
	topPipeTexture = NULL();
	bottomPipeTexture = NULL();
	topPipeHeight = 0;
	bottomPipeHeight = 0;
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
		!bottomPipeTexture->loadTexture(renderer, "assets/pipe/bottom.png")) {
		return false;
	}
	return true;
}

void Pipe::randomPipe() {
	topPipeHeight = MIN_HEIGHT + rand() % (MAX_HEIGHT - MIN_HEIGHT + 1);
	bottomPipeHeight = SCREEN_HEIGHT - topPipeHeight - PIPE_GAP;
}

void Pipe::updatePipe() {
		topPipePosition.x -= PIPE_SPEED;
		bottomPipePosition.x -= PIPE_SPEED;
}

bool Pipe::isOffScreen() {
	return topPipePosition.x + PIPE_WIDTH < 0;
}

void Pipe::renderPipe(SDL_Renderer* renderer) {
	topPipeTexture->renderTexture(renderer, topPipePosition.x, 0 - topPipeHeight);
	bottomPipeTexture->renderTexture(renderer, bottomPipePosition.x, bottomPipeHeight);
}

void Pipe::freePipe() {
	if (topPipeTexture != NULL) {
		topPipeTexture->freeTexture();
		delete topPipeTexture;
	}
	if (bottomPipeTexture != NULL) {
		bottomPipeTexture->freeTexture();
		delete bottomPipeTexture;
	}
}

int Pipe::getPipePosition() {
	return topPipePosition.x;
}
