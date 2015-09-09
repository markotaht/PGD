#include "hall.h"

Hall::Hall(int x, int y, int width, int height):
x1(x),
y1(y),
x2(x+width - 1),
y2(y+height - 1),
_width(abs(width)),
_height(abs(height))
{}

bool Hall::hallIntersection(Hall* const other){
	if (x1 == x2 && other->getY1() == other->getY2() || y1 == y2 && other->getX1() == other->getX2()){
		if (x1 > other->x1 && x1 < other->x2 && y2 < other->getY1() && y2 > other->getY2()) return true;
	}
	return false;
}

int Hall::getX1(){
	return x1;
}

int Hall::getY1(){
	return y1;
}

int Hall::getX2(){
	return x2;
}

int Hall::getY2(){
	return y2;
}

int Hall::getWidth(){
	return _width;
}

int Hall::getHeight(){
	return _height;
}