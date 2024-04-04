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

enum GameStates {
    MENU,
	PREPARE,
	PLAY,
	PAUSE,
	GAME_OVER
};

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Ground* ground;
	Bird* bird;
	Texture* background;
	Texture* gameOverTexture;
	std::vector<Texture*> buttons;
	Texture* flappy;
	Texture* pause;
	Texture* prepare;
	Texture* pauseButton;
	Texture* resumeButton;
	Score* score;
	std::vector<Pipe*> pipes;
	bool isOver;
	bool stop;
	bool prepareGame;
	GameStates gameState;
    ;

public:
	Game();
	~Game();
	bool initSDL();
	bool initGame();
	void prepareScene();
	void presentScene();
	void renderGround();
	void spawnPipe();
	void renderPipe();
	void managePipe();
	void checkCollision();
	void handleInput(SDL_Event& e, bool& quit);
	void updateGame();
	void resetGame();
};

#endif // _GAME__H
