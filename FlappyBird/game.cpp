#include "game.h"

#include <iostream>

Game::Game() {
	window = nullptr;
	renderer = nullptr;
	ground = new Ground();
	background = new Texture();
	gameOverTexture = new Texture();
	bird = new Bird();
	isOver = false;
}

Game::~Game() {
	for (Pipe* &pipe : pipes) {
	    delete pipe;
		pipe = nullptr;
    }
	delete ground;
	delete background;
	delete bird;
	delete gameOverTexture;
	ground = nullptr;
	background = nullptr;
	bird = nullptr;
	gameOverTexture = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool Game::initSDL() {
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize SDL %s", SDL_GetError());
		success = false;
	}
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create window %s", SDL_GetError());
		success = false;
	}
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize SDL %s", SDL_GetError());
		success = false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create renderer %s", SDL_GetError());
		success = false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return success;
}

bool Game::initGame() {
	background->loadTexture(renderer, "assets/image/background.png");
	bird->loadBird(renderer);
	ground->loadGround(renderer, "assets/image/land.png");
	gameOverTexture->loadTexture(renderer, "assets/image/gameOver.png");
	return true;
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void Game::presentScene() {
	SDL_RenderPresent(renderer);
}

void Game::renderGround() {
	ground->updateGround();
	ground->renderGround(renderer);
}

void Game::renderBackground() {
	background->renderTexture(renderer, 0, 0);
}

void Game::updateBird() {
	bird->updateBird();
}

void Game::renderBird() {
	bird->renderBird(renderer);
}

void Game::flapBird() {
	bird->flap();
}

void Game::spawnPipe() {
	Pipe* pipe = new Pipe();
	pipe->loadPipe(renderer);
	pipes.push_back(pipe);
}

void Game::managePipe() {
	for (Pipe* &pipe : pipes) {
		pipe->updatePipe();
	}

	for (auto it = pipes.begin(); it != pipes.end();) {
		if ((*it)->isOffScreen()) {
			delete *it;
			it = pipes.erase(it);
		} else {
			++it;
		}
	}

	if (pipes.empty() || pipes.back()->getTopPipePosition().x < SCREEN_WIDTH - 150) {
		spawnPipe();
	}
}

void Game::renderPipe() {
	for (Pipe* &pipe : pipes) {
		pipe->renderPipe(renderer);
	}
}

void Game::checkCollision() {
	Position birdPos = bird->getPosition();
	//GROUND_HEIGHT = 140, PIPE_GAP = 162, PIPE_WIDTH = 65, PIPE_HEIGHT = 373;
	//BIRD_WIDTH = 34, BIRD_HEIGHT = 24;

	if(birdPos.y + 24 >= SCREEN_HEIGHT - 140) {
	    isOver = true;
		return;
	}

	for (Pipe* &pipe : pipes) {
	    Position topPipePos = pipe->getTopPipePosition();
		Position bottomPipePos = pipe->getTopPipePosition();

		if (birdPos.x + 34 >= topPipePos.x &&  birdPos.x <= topPipePos.x + 65 && birdPos.y <= 373 - topPipePos.y) {
		    isOver = true;
			return;
		}

		if (birdPos.x + 34 >= bottomPipePos.x && birdPos.x <= bottomPipePos.x + 65 && birdPos.y + 24 >= 373 - topPipePos.y + 162) {
		    isOver = true;
			return;
		}
	}

}

void Game::handleGameOver() {
    gameOverTexture->renderTexture(renderer, 50, 150);
}

bool Game::isGameOver() {
    return isOver;
}