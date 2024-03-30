#ifndef _GAME__H
#define _GAME__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <cstdlib>
#include "defs.h"
#include "texture.h"
#include "ground.h"
#include "bird.h"
#include "pipe.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Ground* ground;
	Bird* bird;
	Texture* background;
	std::vector<Pipe*> pipes;
public:
	Game();
	~Game();
	bool initSDL();
	bool initGame();
	void prepareScene();
	void presentScene();
	void renderGround();
	void renderBackground();
	void renderBird();
	void updateBird();
	void flapBird();
	void initPipe();
	void renderPipe();
	void updatePipe();
	void managePipe();
};

#endif // _GAME__H
