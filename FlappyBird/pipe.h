#ifndef _PIPE__H
#define _PIPE__H

#include "texture.h"
#include "defs.h"
//todo: sua initialspawn bo pipeWidth
class Pipe {
private:
	Texture* topPipeTexture;
	Texture* bottomPipeTexture;
	Position topPipePosition;
	Position bottomPipePosition;
	const int minHeight = 95;
	const int maxHeight = 250;
	const int pipeGap = 162;
	const int pipeSpeed = 2;
    const int pipeWidth = 65;
    const int pipeHeight = 373;
public:
	Pipe();
	~Pipe();

	bool loadPipe(SDL_Renderer* renderer);
	void renderPipe(SDL_Renderer* renderer);
	void updatePipe();
	void updateDeadPipe();
	void renderDeadPipe(SDL_Renderer* renderer);
	bool isOffScreen();
	void randomPipe();
	void freePipe();
    Position getTopPipePosition();
    Position getBottomPipePosition();
};

#endif // _PIPE__H