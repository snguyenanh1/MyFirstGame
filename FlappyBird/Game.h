#ifndef _GAME__H
#define _GAME__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <ctime>
#include "defs.h"
#include "texture.h"
#include "ground.h"
#include "bird.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Ground* ground;
	Bird* bird;
	Texture* background;
public:
	Game();
	~Game();
	bool initSDL();
	bool initGame();
	void loadBackground();
	void prepareScene();
	void presentScene();
	void initGround();
	void renderGround();
	void renderBackground();
	void initBird();
	void renderBird();
	void updateBird();
	void flapBird();
};

#endif // _GAME__H
