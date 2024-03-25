#include "defs.h"

const int SCREEN_WIDTH = 350;
const int SCREEN_HEIGHT = 625;
const char* WINDOW_TITLE = "Flappy Bird";

void Position::setPosition(const int x, const int y) {
	this->x = x;
	this->y = y;
}