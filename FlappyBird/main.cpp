#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
	Game game;

	game.init();
	game.renderTexture(game.getFlappyBirdTexture(), 0, 0);
	game.presentScene();
	game.handleEvents();
	return 0;
}
