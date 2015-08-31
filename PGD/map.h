#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL.h>

#include <stdlib.h>
#include <time.h>

#include "floor.h"
#include "tile.h"
#include "room.h"
#include "wall.h"
#include "leaf.h"

class Map{
private:
	std::vector<Tile*> tiles;
	std::vector<Room*> rooms;
	std::vector<Hall*> halls;

	int Mwidth, Mheight;
public:
	Map(int width, int height);
	void generateRooms();
	void render(SDL_Renderer* renderer);
};
#endif