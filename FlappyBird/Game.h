#ifndef _GAME__H
#define _GAME__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

const int SCREEN_HEIGHT = 625;
const int SCREEN_WIDTH = 350;
const char* WINDOW_TITLE = "Flappy Bird";

struct Position {
	int x, y;
	int angle;
	int state;

	void getPosition(const int x, const int y);
};

struct Input {
	enum Type { QUIT, PLAY, NONE, PAUSE };
	Type type;
};


#endif // _GAME__H