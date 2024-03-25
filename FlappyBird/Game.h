#ifndef _GAME__H
#define _GAME__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "texture.h"
#include "ground.h"

class Game {
public:
	Game();
	~Game();
	bool initGame();
	//void loadBackground();
	void prepareScene();
	void presentScene();
	void initGround();
	void renderGround();
	void renderBackground();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Ground* ground;
};

#endif // _GAME__H
