#ifndef _GAME__H
#define _GAME__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "land.h"
#include "defs.h"


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

class Game : public Graphics {
public:
	Land land;
public:
	Game();
	bool init();
	void renderLand();
};

#endif // _GAME__H