#ifndef _FUNCTIONS__H
#define _FUNCTIONS__H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream> //xoa

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* WINDOW_TITLE = "ShittyMario";


void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

/*bool checkIfMousePressed(int x, int y, int w1, int w2, int h1, int h2) {
    SDL_Event event;
    while (true) {
        SDL_GetMouseState(&x, &y);
        std::cout << x << " " << y << std::endl;
        SDL_PollEvent(&event);
        switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && x >= w1 && x <= w2 && y >= w1 && y <= w2) {
					return true;
				}
				break;
            case SDL_QUIT:
                exit(0);
                break;
		}
        SDL_Delay(100);
    }

}*/





#endif // _FUNCTIONS__H
