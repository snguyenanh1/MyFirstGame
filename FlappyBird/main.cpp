#include "game.h"
#include <ctime>
#include <cstdlib>


const int TARGET_FPS = 60;  
Uint32 frameStart, frameTime;

int main(int argc, char* argv[]) {
    srand(time(nullptr));
    Game game;
    game.initSDL();
    game.initGame();


    SDL_Event e;
    bool quit = false;
//TODO: fix check collision

    while (!quit) {
        game.prepareScene();
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
           
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                if(!game.isGameOver())
                    game.flapBird();
            }
        }
        if (game.isGameOver()) {
            game.handleGameOver();
        }
        game.checkCollision();
        game.updateBird(); 
        game.managePipe();
        game.renderBackground();
        game.renderPipe();
        game.renderBird();
        game.renderGround(); 
        game.presentScene(); 
        if (game.isGameOver()) {
            break;
        }
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000 / TARGET_FPS) {
          SDL_Delay((1000 / TARGET_FPS) - frameTime);
        }
    }

    return 0;
}