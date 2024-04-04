#include "game.h"
#include <ctime>
#include <cstdlib>


const int TARGET_FPS = 60;  
Uint32 frameStart, frameTime;

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    Game* game = new Game();
    game->initSDL();
    game->initGame();
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        frameStart = SDL_GetTicks();
        game->prepareScene();
        while (SDL_PollEvent(&e)) {
            game->handleInput(e, quit);
        }
        game->updateGame();
        game->presentScene();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000 / TARGET_FPS) {
          SDL_Delay((1000 / TARGET_FPS) - frameTime);
        }
    }
    delete game;
    game = nullptr;
    return 0;
}