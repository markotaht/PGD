#include "map.h"

Map::Map(int width, int height):
Mwidth(width),
Mheight(height)
{
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			tiles.push_back(new Wall(15 * x, 15*y));
		}
	}
}

void Map::render(SDL_Renderer* renderer){
	for (std::vector<Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++){
		(*it)->render(renderer);
	}
}

void Map::generateRooms(){
	srand(time(NULL));
	std::vector<Leaf*> leaves;
	Leaf root(0, 0, Mwidth, Mheight);
	leaves.push_back(&root);
	bool split = true;
	while (split){
		split = false;
		std::vector<Leaf*> temp;
		for (Leaf* l : leaves){
			if (l->getLeft() == NULL && l->getRight() == NULL){
				if (l->getWidth() > MAX_ROOM_SIZE || l->getHeight() > MAX_ROOM_SIZE || rand() > 0.25){
					if (l->split()){
						temp.push_back(l->getLeft());
						temp.push_back(l->getRight());
						split = true;
					}
				}
			}
		}
		for (Leaf* l : temp){
			leaves.push_back(l);
		}
	}
	root.createRoom();

	for (Leaf* l : leaves){
		if (l->getRoom() != NULL){
			Room* room = l->getRoom();
			rooms.push_back(room);
			for (int x = room->getX1(); x < room->getX2(); x++){
				for (int y = room->getY1(); y < room->getY2(); y++){
					tiles[x + y * Mheight] = new Floor(x * 15, y * 15);
				}
			}
			if (l->getHall().size() != 0){
				for (Hall* h : l->getHall()){
					halls.push_back(h);
					for (int x = h->getX1(); x < h->getX2(); x++){
						for (int y = h->getY1(); y < h->getY2(); y++){
							tiles[x + y * Mheight] = new Floor(x * 15, y * 15);
						}
					}
				}
			}
		}
	}
}
