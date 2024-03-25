#include "texture.h"

Texture::Texture() {
	texture = NULL;
	textureWidth = 0;
	textureHeight = 0;
}

Texture::~Texture() {
	freeTexture();
}

bool Texture::loadTexture(SDL_Renderer* renderer, const char* path) {
	bool success = true;
	freeTexture();
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", SDL_GetError());
		success = false;
	}
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	return success;
}

void Texture::renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle,
							SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect dest = { x, y, textureWidth, textureHeight };
	if (clip != NULL) {
		dest.w = clip->w;
		dest.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &dest, angle, center, flip);
}
void Texture::renderCopy(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}
void Texture::freeTexture() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}