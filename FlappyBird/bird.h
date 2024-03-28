#ifndef _BIRD__H
#define _BIRD__H

#include "defs.h"
#include "texture.h"
#include <vector>
#include <string>

const std::vector<std::vector<std::string>> paths = {
	{"assets/birds/blue/down.png", "assets/birds/blue/mid.png", "assets/birds/blue/up.png"},
	{"assets/birds/yellow/down.png", "assets/birds/yellow/mid.png", "assets/birds/yellow/up.png"},
	{"assets/birds/red/down.png", "assets/birds/red/mid.png", "assets/birds/red/up.png"},
};

class Bird {
private:
	std::vector<Texture*> birdTextures;
	int currentFrame = 1;
	Position birdPosition;
	double speed;
	double angle;
	const double gravity = 0.5;
	const double maxSpeed = 12.0;
	const double maxAngle = 45.0;
	//const double step = 0.1;
	const double flapSpeed = -9.0;
	bool isFlapping;
	bool isFlappingUp;
public:
	Bird();
	~Bird();
	bool loadBird(SDL_Renderer* renderer);
	void updateBird();
	void flap();
	void renderBird(SDL_Renderer* renderer);
	void freeBird();
};

#endif // _BIRD__H