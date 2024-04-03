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
#include "score.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Ground* ground;
	Bird* bird;
	Texture* background;
	Texture* gameOverTexture;
	Score* score;
	//Texture* medalTexture;
	//std::vector<int> points;
	std::vector<Pipe*> pipes;
	bool isOver;
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
	void spawnPipe();
	void renderPipe();
	void managePipe();
	void checkCollision();
	void renderGameOver();
	bool isGameOver();
	bool updateDeadBird();
	void renderSmallScore();
	void incrementScore();
	void saveBestScore();
	void checkBestScore();
	void renderScore();
	void renderMedal();
};

#endif // _GAME__H
