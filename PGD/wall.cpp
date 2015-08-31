#include "wall.h"

Wall::Wall(int x, int y) : Tile(x, y){
	rect.h = height;
	rect.w = width;
	rect.x = x;
	rect.y = y;
}

bool Wall::render(SDL_Renderer* renderer){
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
	return true;
}