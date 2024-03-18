#ifndef _FUNCTIONS__H
#define _FUNCTIONS__H

#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 350;
const int SCREEN_HEIGHT = 485;
const char* WINDOW_TITLE = "SDL_Tutorial";


void waitUntilKeyPressed() {

    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }

}

#endif

