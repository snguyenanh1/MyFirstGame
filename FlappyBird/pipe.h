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
	const int minHeight = 95;
	const int maxHeight = 250;
	const int pipeGap = 162;
	//const int distance = 80;
	const int pipeSpeed = 2;
    const int pipeWidth = 65;
    const int pipeHeight = 373;
	int initialSpawnPosition = SCREEN_WIDTH + pipeWidth;
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
};

#endif // _PIPE__H