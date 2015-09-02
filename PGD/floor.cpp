#include "floor.h"

Floor::Floor(int x, int y) : Tile(x, y){
	rect.h = height;
	rect.w = width;
	rect.x = x;
	rect.y = y;
	r = 125;
	g = 125;
	b = 125;
}

bool Floor::render(SDL_Renderer* renderer){
	SDL_SetRenderDrawColor(renderer, r, g, b, 0x88);
	SDL_RenderFillRect(renderer, &rect);
	return true;
}