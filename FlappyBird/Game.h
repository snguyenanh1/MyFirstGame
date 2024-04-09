#ifndef _GAME__H
#define _GAME__H

#include "bird.h"
#include "defs.h"
#include "ground.h"
#include "pipe.h"
#include "score.h"
#include "sound.h"
#include "texture.h"
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

enum GameStates {
    MENU,
	PREPARE,
	PLAY,
	PAUSE,
	AFTER_DEAD,
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
	std::vector<Texture*> soundButton;
	Sound* backgroundMusic;
	Sound* gameOverMedal;
	Sound* gameOverNoMedal;
	Sound* jump;
	Sound* dead;
	Sound* bestScore;
	Sound* backgroundMenu;
	Sound* prepareMusic;
	Sound* gameOverMusic;
	Sound* click;
	bool isOver;
	bool stop;
	GameStates gameState;
	bool soundOn;
    int birdType;
	int gameOverPosY = SCREEN_HEIGHT;
	int deadDuration;
	int deadTimer;
	int gameOverDuration;
	int gameOverTimer;
    int gameOverDurationNoMedal;
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
    bool updateGameOver();
    void resetGame();
    bool deadAnimation();
};

#endif // _GAME__H
