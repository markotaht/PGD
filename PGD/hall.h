#ifndef HALL_H
#define HALL_H

#include <SDL.h>
class Hall{
private:
	int x1, y1;
	int x2, y2;
	int _width, _height;
public:
	Hall(int x, int y, int width, int height);

	int getX1();
	int getY1();
	int getX2();
	int getY2();
	int getWidth();
	int getHeight();

};
#endif