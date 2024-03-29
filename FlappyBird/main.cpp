#include "game.h"


const int TARGET_FPS = 60;  
Uint32 frameStart, frameTime;


int main(int argc, char* argv[]) {
    Game game;
    game.initSDL();
    game.initGame();
    game.prepareScene();
    game.initGround();
    game.initBird();

    SDL_Event e;
    bool quit = false;


    while (!quit) {
    
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
           
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                game.flapBird();
            }
        }

        game.updateBird(); 
        game.prepareScene(); 
        game.renderBackground();
        game.renderBird(); 
        game.renderGround(); 
        game.presentScene(); 

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < 1000 / TARGET_FPS) {
          SDL_Delay((1000 / TARGET_FPS) - frameTime);
        }
    }

    return 0;
}