#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "floor.h"
#include "tile.h"
#include "room.h"
#include "wall.h"
#include "leaf.h"

#define TILE_SIZE 5

class Map{
private:
	std::vector<Tile*> tiles;
	std::vector<Room*> rooms;
	std::vector<Hall*> halls;

	std::vector<bool> cells;

	std::vector<bool> doGenerationStep(std::vector<bool> cells);
	int countNeigbours(std::vector<bool> cells, int x, int y);

	int Mwidth, Mheight;
	int chasetostartAlive = 50;
	int deathlimit = 5;
	int birthlimit = 3;
public:
	Map(int width, int height);
	void generateMap();
	void generateRooms();
	void render(SDL_Renderer* renderer);
	void createHalls();
};
#endif