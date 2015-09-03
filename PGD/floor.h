#ifndef FLOOR_H
#define FLOOR_H

#include <SDL.h>
#include <SDL_image.h>
#include "tile.h"

class Floor : public Tile{
private:
	SDL_Rect rect;
public:
	int r, g, b,a;
	Floor(int x, int y);
	bool render(SDL_Renderer* renderer);
};
#endif 