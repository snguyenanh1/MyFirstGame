#include "texture.h"

Texture::Texture() {
	texture = nullptr;
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
	if (texture == nullptr) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", SDL_GetError());
		success = false;
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
	return success;
}

void Texture::renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle,
							SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect dest = { x, y, textureWidth, textureHeight };
	if (clip != nullptr) {
		dest.w = clip->w;
		dest.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &dest, angle, center, flip);
}

void Texture::renderCopy(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void Texture::freeTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

int Texture::getTextureWidth()  {
	return textureWidth;
}

int Texture::getTextureHeight() {
	return textureHeight;
}