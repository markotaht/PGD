#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Tile{
protected:
	int width, height;
	int _x, _y;
public:
	Tile();
	Tile(int x, int y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	virtual bool render(SDL_Renderer* renderer)
	{
		return false;
	};
};
#endif