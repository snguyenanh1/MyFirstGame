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
#include "sound.h"

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
	std::vector<Bird*> birds;
	Texture* background;
	Texture* gameOverTexture;
	std::vector<Texture*> buttons;
	Texture* flappy;
	Texture* pause;
	Texture* prepare;
	Texture* pauseButton;
	Texture* resumeButton;
	Texture* leftButton;
	Texture* rightButton;
	Score* score;
	std::vector<Pipe*> pipes;
	Sound* backgroundMusic;
	Sound* gameOverMedal;
	Sound* gameOverNoMedal;
	Sound* jump;
	Sound* dead;
	bool isOver;
	bool stop;
	bool prepareGame;
	bool finishedDead;
	GameStates gameState;
	int birdType;
public:
	Game();
	~Game();
	bool initSDL();
    void initGame();
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
    bool deadAnimation();
};

#endif // _GAME__H
