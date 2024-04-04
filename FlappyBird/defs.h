#ifndef _DEFS__H
#define _DEFS__H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const char* WINDOW_TITLE;


struct Position {
	int x, y;

	void setPosition(const int x, const int y);
};


#endif // _DEFS__H