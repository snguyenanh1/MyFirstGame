#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"


class Graphics {
protected:  
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int textureWidth;
	int textureHeight;
public:
	Graphics();
	~Graphics();
	bool loadTexture(const char* path, double scale = 1);
	void renderTexture(int x, int y, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderPresent();
	void freeTexture();
	//SDL_Texture* getTexture();
	//int getWidth();
	//int getHeight();
};

#endif // _GRAPHICS__H