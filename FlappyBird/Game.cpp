#include "game.h"

void Game::logErrorAndExit(const char* msg, const char* error) {
	
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
	
	SDL_Quit();
}

void Game::init() {
	
	isRunning = true; 

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logErrorAndExit("SDL_Init", SDL_GetError());

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (window == nullptr)
		logErrorAndExit("CreateWindow", SDL_GetError());

	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
		logErrorAndExit("SDL_image error:", IMG_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::prepareScene(SDL_Texture* background) {
	
	SDL_RenderClear(renderer);
	
	SDL_RenderCopy(renderer, background, NULL, NULL);

}

void Game::presentScene() {
	
	SDL_RenderPresent(renderer);
}

SDL_Texture* Game::loadTexture(const char* filename) {
	
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading % s", filename);
	
	SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
	
	if (texture == NULL)
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}

void Game::renderTexture(SDL_Texture* texture, int x, int y) {
	
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);

}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void Game::handleEvents() {
	
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP)
	}
}