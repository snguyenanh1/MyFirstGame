#ifndef _PIPE__H
#define _PIPE__H

#include "texture.h"
#include "defs.h"
#include <vector>
#include <string>

const std::vector<std::vector<std::string>> paths = {
	{"assets/pipe/green/bottom.png", "assets/pipe/green/top.png"},
	{"assets/pipe/red/bottom.png", "assets/pipe/red/top.png"},
};

class Pipe {
private:
	Texture* topPipeTexture;
	Texture* bottomPipeTexture;
	Position topPipePosition;
	Position bottomPipePosition;
	int pipeWidth, topPipeHeight, bottomPipeHeight;
	const int MIN_HEIGHT = 50;
	const int MAX_HEIGHT = 160;
	const int PIPE_GAP = 140;
public:
	Pipe();
	~Pipe();

	void loadPipe(SDL_Renderer* renderer);
	void renderPipe(SDL_Renderer* renderer);
	void movePipe(int distance);
	void randomPipe();


};

#endif // _PIPE__H