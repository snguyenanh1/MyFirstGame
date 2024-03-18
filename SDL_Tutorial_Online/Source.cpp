#include <iostream>
#include "gameFunctions.h"
#include "graphics.h"

int main(int argc, char* argv[]) {
	Graphics graphics;
	graphics.init();
	SDL_Texture* background = graphics.loadTexture("images/background.png");
	graphics.prepareScene(background);

	graphics.presentScene();
	waitUntilKeyPressed();

	/*SDL_Texture* spongeBob = graphics.loadTexture("images/Spongebob.png");
	graphics.renderTexture(spongeBob, 200, 200);*/

	graphics.presentScene();
	waitUntilKeyPressed();

	//SDL_DestroyTexture(spongeBob);
	//spongeBob = NULL;

	SDL_DestroyTexture(background);
	background = NULL;

	graphics.quit();

	return 0;
}
