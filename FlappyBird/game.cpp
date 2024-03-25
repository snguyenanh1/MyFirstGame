#include "game.h"

Game::Game() {
	window = NULL;
	renderer = NULL;
	ground = new Ground();
}

Game::~Game() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool Game::initGame() {
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize SDL %s", SDL_GetError());
		success = false;
	}
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create window %s", SDL_GetError());
		success = false;
	}
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Initialize SDL %s", SDL_GetError());
		success = false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create renderer %s", SDL_GetError());
		success = false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	return success;
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void Game::presentScene() {
	SDL_RenderPresent(renderer);
}

void Game::initGround() {
	ground->loadGround(renderer, "assets/image/land.png");
}

void Game::renderGround() {
	ground->updateGround();
	ground->renderGround(renderer);
}

void Game::renderBackground() {
	Texture* background = new Texture();
	background->loadTexture(renderer, "assets/image/background.png");
	background->renderTexture(renderer, 0, 0);
	presentScene();
}