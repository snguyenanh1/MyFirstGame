#include "TextureManager.h"

LTexture::LTexture() {
	texture = NULL;
	textureWidth = 0;
	textureHeight = 0;
}

LTexture::~LTexture() {
	freeTexture();
}

