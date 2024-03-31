#ifndef _TEXTURE__H
#define _TEXTURE__H

#include <SDL.h>
#include <SDL_image.h>

class Texture {
private:
	SDL_Texture* texture;
	int textureWidth;
	int textureHeight;
public:
	Texture();
	~Texture();
	bool loadTexture(SDL_Renderer* renderer, const char* path);
	void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0,		
					   SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderCopy(SDL_Renderer* renderer);
	void freeTexture();
	int getTextureWidth();
	int getTextureHeight();

};

#endif // _TEXTURE__H