#include "game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.initGame();
    game.renderBackground();
    game.initGround();
    game.initBird();

    SDL_Event e;
    bool quit = false;


    while (!quit) {
       game.prepareScene();
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

        SDL_Delay(15);
    }

    return 0;
}