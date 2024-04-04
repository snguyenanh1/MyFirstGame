#ifndef _BIRD__H
#define _BIRD__H

#include <string>
#include <vector>

#include "defs.h"
#include "texture.h"

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
    const double gravity = 0.6;
    const double maxSpeed = 12.0;
    const double maxAngle = 45.0;
    const double flapSpeed = -10.0;
    bool isFlapping;
    bool isFlappingUp;
    int frameCounter;
    const int framePerChange = 15;

public:
    Bird();
    ~Bird();
    bool loadBird(SDL_Renderer* renderer);
    void updateBird();
    void ticks();
    void flap();
    void renderBird(SDL_Renderer* renderer);
    void freeBird();
    Position getPosition();
    bool updateDeadBird();
    void resetBird();
};

#endif // _BIRD__H
