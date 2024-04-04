#ifndef _SCORE__H
#define _SCORE__H

#include <vector>
#include <string>
#include "defs.h"
#include "pipe.h"
#include "texture.h"

class Score {
private:
	std::vector<Texture*> smallTextures;
	std::vector<Texture*> largeTextures;
	std::vector<Texture*> medalTextures;
	int currentScore;
	int bestScore;
public:
	Score();
   ~Score();
    bool loadImage(SDL_Renderer* renderer);
	void incrementScore(std::vector<Pipe*>& pipes, Position birdPosition);
	void renderSmallScore(SDL_Renderer* renderer);
	void renderLargeScore(SDL_Renderer* renderer);
	void renderMedal(SDL_Renderer* renderer);
	void freeScore();
    void resetScore();
    void saveBestScore();
	void checkBestScore();
};

#endif // _SCORE__H