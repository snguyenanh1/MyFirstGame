#ifndef __MENU__H
#define __MENU__H

#include "graphic.h"

struct Menu {
	Graphics menu;
	void loadMenu() {
		menu.init();
		SDL_Texture* texture = menu.loadTexture("asset/img/menu_imgs/menu.png");
		menu.prepareScene(texture);
		menu.presentScene();
	}
	void checkIfMousePressed() {
		SDL_Event event;
		int x, y;
		while (true) {
			SDL_GetMouseState(&x, &y);
			SDL_PollEvent(&event);
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT && x >= 199 && x <= 350 && y >= 266 && y <= 301) {
					SDL_Texture* _background = menu.loadTexture("asset/img/other_imgs/background.jpg");
					menu.prepareScene(_background);
					menu.presentScene();
					waitUntilKeyPressed();
					menu.quit();
				}
				if (event.button.button == SDL_BUTTON_LEFT && x >= 235 && x <= 314 && y >= 326 && y <= 361) {
					menu.quit();
				}
				break;
			case SDL_QUIT:
				exit(0);
				break;
			}
			SDL_Delay(50);
		}
	}
};

#endif // __MENU__H