#include "game.h"
#include "land.h"
#include "graphics.h"

int main(int argc, char* argv[]) {
    Game game;
    
    bool quit = false;

    // Event handler
    SDL_Event e;

    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
     
        // Update the land
        game.land.updateLand();

        // Clear screen

        // Render the land
        game.land.renderLand();

        // Update screen
        game.renderPresent();
    }
    return 0;
}