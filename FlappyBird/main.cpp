#include "game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.initGame();
    game.renderBackground();
    game.initGround();

    SDL_Event e;
    bool quit = false;


    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        game.renderGround();
        game.presentScene();
        SDL_Delay(15); //them vao het bug ???
    }
    return 0;
}