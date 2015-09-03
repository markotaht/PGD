#include "hall.h"

Hall::Hall(int x, int y, int width, int height):
x1(x),
y1(y),
x2(x+width),
y2(y+height),
_width(abs(width)),
_height(abs(height))
{}

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