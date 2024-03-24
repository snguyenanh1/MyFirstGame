#include "Graphics.h"

Graphics::Graphics() {
	texture = NULL;
	int textureWidth = 0;
	int textureHeight = 0;
}

Graphics::~Graphics() {
	freeTexture();
}

bool Graphics::loadTexture(const char* path, double scale) {
	freeTexture();
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture: %s", IMG_GetError());
		return false;
	}
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	textureWidth *= scale;
	textureHeight *= scale;
	return true;
}

void Graphics::renderTexture(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect dest = { x, y, textureWidth, textureHeight };
	dest.x = x;
	dest.y = y;
	if (clip != NULL) {
		dest.w = clip->w;
		dest.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &dest, angle, center, flip);
}
 
void Graphics::freeTexture() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}

/*SDL_Texture* Graphics::getTexture() {
	return texture;
}*/
void Graphics::renderPresent() {
	SDL_RenderPresent(renderer);
}
