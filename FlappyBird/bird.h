#ifndef _BIRD__H
#define _BIRD__H

#include "defs.h"
#include "texture.h"
#include <vector>
#include <string>


class Bird {
private:
	std::vector<Texture*> birdTextures;
	Position birdPosition;
	float velocity, rotation;
	const float gravity, maxVelocity, flappingVelocity, maxRotation;
	bool isFlapping, isFlappingUp;
public:
	Bird();
	~Bird();
	bool loadBird(SDL_Renderer* renderer, const std::vector<std::string>& texturePaths);
	void renderBird(SDL_Renderer* renderer);
};