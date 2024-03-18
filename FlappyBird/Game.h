#ifndef _GAME__H
#define _GAME__H

#include <SDL.h>
#include <SDL_image.h>


class Game {
private:
	const int SCREEN_HEIGHT = 485;
	const int SCREEN_WIDTH = 350;
	const char* WINDOW_TITLE = "Flappy Bird";
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	Game();
	~Game();
	void init();
	void render();
	void update();
	void handleEvents();
	void logErrorAndExit(const char* msg, const char* error);
	void clean();
	void prepareScene(SDL_Texture* background);
	void presentScene();
	SDL_Texture* loadTexture(const char* filename);
	void renderTexture(SDL_Texture* texture, int x, int y);
	void GetGameState();
};

#endif // _GAME__H