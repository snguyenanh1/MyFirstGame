#ifndef _GROUND__H
#define _GROUND__H

#include "texture.h"
#include "defs.h"

const int GROUND_WIDTH = 350;
const int GROUND_HEIGHT = 140;
class Ground {
public:
	Ground();
	~Ground();
	bool loadGround(SDL_Renderer* renderer, const char* path);
	void updateGround();
	void renderGround(SDL_Renderer* renderer);
	void freeGround();
private:
	Texture* groundTexture;
	SDL_Rect groundRect;
	int scrollSpeed;
};

#endif // _GROUND__H