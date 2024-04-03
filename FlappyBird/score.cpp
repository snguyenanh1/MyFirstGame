#include "score.h"

#include <string>
#include <fstream>


Score::Score() {
    currentScore = 0;
    bestScore = 0;
    std::ifstream file("assets/data/score.txt");
    file >> bestScore;
    file.close();
}

Score::~Score() {
    freeScore();
}

bool Score::loadImage(SDL_Renderer* renderer) {
    for (int i = 0; i < 10; i++) {
        Texture* score = new Texture();
        if (!score->loadTexture(renderer, ("assets/number/small/" + std::to_string(i) + ".png").c_str())) {
            return false;
        }
        smallTextures.push_back(score);
    }

    for (int i = 0; i < 10; i++) {
        Texture* score = new Texture();
        if (!score->loadTexture(renderer, ("assets/number/large/" + std::to_string(i) + ".png").c_str())) {
            return false;
        }
        largeTextures.push_back(score);
    }

    for (int i = 0; i < 4; i++) {
        Texture* medal = new Texture();
        if (!medal->loadTexture(renderer, ("assets/medal/" + std::to_string(i) + ".png").c_str())) {
            return false;
        }
        medalTextures.push_back(medal);
    }
    return true;
}

void Score::incrementScore(Pipe* pipe, Position birdPosition) {
    if (!pipe->getScored() && pipe->getTopPipePosition().x + 32 < birdPosition.x) {
        currentScore++;
        pipe->setScored(true);
    }
}

void Score::renderSmallScore(SDL_Renderer* renderer) {
    std::string score = std::to_string(currentScore);
    std::string best = std::to_string(bestScore);
    int width = smallTextures[0]->getTextureWidth();
    int scorePos = 223 - width + 50;
    int bestPos = 223 - width + 50;
    for (int i = score.length() - 1; i >= 0; i--) {
        smallTextures[score[i] - '0']->renderTexture(renderer, scorePos, 265);
        scorePos -= width;
    }
    for (int i = best.length() - 1; i >= 0; i--) {
        smallTextures[best[i] - '0']->renderTexture(renderer, bestPos, 314);
        bestPos -= width;
    }
}

void Score::renderLargeScore(SDL_Renderer* renderer) {
    std::string score = std::to_string(currentScore);
    int width = largeTextures[0]->getTextureWidth();
    int totalWidth = width*score.length();
    int startPos = (SCREEN_WIDTH - totalWidth) / 2;
    for (char digit : score) {
        int digitIndex = digit - '0';
        largeTextures[digitIndex]->renderTexture(renderer, startPos, 50);
        startPos += width;
    }
}

void Score::saveBestScore() {
    std::ofstream file("assets/data/score.txt");
    file << bestScore;
    file.close();
}

void Score::checkBestScore() {
    if (currentScore > bestScore) {
        bestScore = currentScore;
    }
}

void Score::renderMedal(SDL_Renderer* renderer) {
    if (currentScore < 3) {
        return;
    }
    else if (currentScore < 6) {
        medalTextures[0]->renderTexture(renderer, 75, 277);
    }
    else if (currentScore < 9) {
        medalTextures[1]->renderTexture(renderer, 75, 277);
    }
    else if (currentScore < 15) {
        medalTextures[2]->renderTexture(renderer, 75, 277);
    }
    else {
        medalTextures[3]->renderTexture(renderer, 75, 277);
    }
}

void Score::freeScore() {
    for (Texture* & texture : smallTextures) {
        texture->freeTexture();
    }
    for (Texture* & texture : largeTextures) {
        texture->freeTexture();
    }
    for (Texture* & texture : medalTextures) {
        texture->freeTexture();
    }
}
