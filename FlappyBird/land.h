#ifndef _LAND__H
#define _LAND__H


#include "graphics.h"
#include "defs.h"

const int LAND_HEIGHT = 140;
const int LAND_WIDTH = 350;

class Land : public Graphics {
private:
	SDL_Rect destRect;
	int scrollSpeed;
public:
	void init();
	~Land();
	void updateLand();
	void renderLand();
};

	#endif // _LAND__H