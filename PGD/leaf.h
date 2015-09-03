#ifndef LEAF_H
#define LEAF_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <iostream>
#include "room.h"
#include "hall.h"

#define MIN_ROOM_SIZE 6
#define MAX_ROOM_SIZE 25

enum Location{UP, MID, DOWN, LEFT, OVER, RIGHT};
class Leaf{
private:

	Leaf* leftChild;
	Leaf* rightChild;
	Room* room;
	std::vector<Hall*> halls;

	int _x, _y;
	int _width, _height;
public:
	Leaf(int x, int y, int width, int height);
	bool split();
	void createRoom();
	void createHall(Room* l, Room* r);
	Leaf* getLeft();
	Leaf* getRight();
	Room* getRoom();
	Room* getRandomChildRoom();
	std::vector<Hall*> getHall();
	int getWidth();
	int getHeight();
	int getRandom(int min, int max);
};

#endif