#include "tile.h"

Tile::Tile():
width(0),
height(0),
_x(0),
_y(0)
{
}
Tile::Tile(int x, int y):
width(15),
height(15),
_x(x),
_y(y)
{
}

int Tile::getHeight(){
	return height;
}

int Tile::getWidth(){
	return width;
}

int Tile::getX(){
	return _x;
}

int Tile::getY(){
	return _y;
}