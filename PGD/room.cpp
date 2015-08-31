#include "room.h"

Room::Room(int x, int y, int width, int height) :
x1(x),
x2(x + width),
y1(y),
y2(y + height),
Rwidth(width),
Rheight(height)
{
	center = { x + width / 2, y + height / 2 };
}

bool Room::intersect(const Room *other){
	return x1 <= other->x2 && x2 >= other->x1
		&& y1 <= other->y2 && y2 >= other->y1;
}

int Room::getX1(){
	return x1;
}

int Room::getY1(){
	return y1;
}

int Room::getX2(){
	return x2;
}

int Room::getY2(){
	return y2;
}

int Room::getWidth(){
	return Rwidth;
}

int Room::getHeight(){
	return Rheight;
}

SDL_Point Room::getCenter(){
	return center;
}