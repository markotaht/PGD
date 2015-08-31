#include "floor.h"

Floor::Floor(int x, int y) : Tile(x, y){
	rect.h = height;
	rect.w = width;
	rect.x = x;
	rect.y = y;
}

bool Floor::render(SDL_Renderer* renderer){
	SDL_SetRenderDrawColor(renderer, 0x88, 0x88, 0x88, 0x88);
	SDL_RenderFillRect(renderer, &rect);
	return true;
}