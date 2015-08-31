#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include <SDL_image.h>
#include "tile.h"

class Wall : public Tile{
private:
	SDL_Rect rect;
public:
	Wall(int x, int y);
	bool render(SDL_Renderer* renderer);
};
#endif 