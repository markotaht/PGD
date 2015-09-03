#ifndef ROOM_H
#define ROOM_H

#include <SDL.h>
#include <vector>
#include "floor.h"

class Room{
private:
//Room coords in grid
	int x1, x2;
	int y1, y2;

	int Rwidth, Rheight;
	std::vector<Room*> connections;

	SDL_Point center;
public:
	Room(int x, int y, int width, int height);

	bool intersect(const Room *other);
	bool checkConnection(const Room* other);
	std::vector<Room*> getConnections();
	void setConnections(Room* room);
	int getX1();
	int getY1();
	int getX2();
	int getY2();
	int getWidth();
	int getHeight();
	SDL_Point getCenter();
};
#endif