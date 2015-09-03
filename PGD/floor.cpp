#include "floor.h"

Floor::Floor(int x, int y) : Tile(x, y){
	rect.h = height;
	rect.w = width;
	rect.x = x;
	rect.y = y;
	r = 125;
	g = 125;
	b = 125;
	a = 0;
}

bool Floor::render(SDL_Renderer* renderer){
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);
	return true;
}