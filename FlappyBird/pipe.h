#ifndef _PIPE__H
#define _PIPE__H

#include "texture.h"
#include "defs.h"

class Pipe {
private:
	Texture* topPipeTexture;
	Texture* bottomPipeTexture;
	Position topPipePosition;
	Position bottomPipePosition;
	const int MIN_HEIGHT = 95;
	const int MAX_HEIGHT = 250;
	const int PIPE_GAP = 80;
	//const int distance = 80;
	const int PIPE_SPEED = 2;
	const int PIPE_WIDTH = 65;
	const int PIPE_HEIGHT = 373;
	int initialSpawnPosition = SCREEN_WIDTH + PIPE_WIDTH;
public:
	Pipe();
	~Pipe();

	bool loadPipe(SDL_Renderer* renderer);
	void renderPipe(SDL_Renderer* renderer);
	void updatePipe();
	bool isOffScreen();
	void randomPipe();
	void freePipe();
    Position getTopPipePosition();
    Position getBottomPipePosition();
    int getPipeWidth();
    int getPipeHeight();

};

#endif // _PIPE__H