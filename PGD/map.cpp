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
	std::vector<Leaf*> leaves;
	Leaf root(0, 0, Mwidth, Mheight);
	leaves.push_back(&root);
	std::vector<Leaf*> temp2;
	temp2.push_back(&root);
	bool split = true;
	while (split){
		split = false;
		std::vector<Leaf*> temp;
		for (Leaf* l : temp2){
			if (l->getLeft() == NULL && l->getRight() == NULL){
				if (l->getWidth() > MAX_ROOM_SIZE || l->getHeight() > MAX_ROOM_SIZE || rand() % 10> 5){
					if (l->split()){
						temp.push_back(l->getLeft());
						temp.push_back(l->getRight());
						split = true;
					}
				}
			}
		}
		temp2.clear();
		for (Leaf* l : temp){
			leaves.push_back(l);
			temp2.push_back(l);
		}
	}
	root.createRoom();
	//root.createHall(root.getLeft()->getRandomChildRoom(), root.getRight()->getRandomChildRoom());
	/*Room * r = new Room(1, 1, 3, 3);
	Room * l = new Room(6, 6, 3, 3);
	rooms.push_back(r);
	rooms.push_back(l);
	root.createHall(r, l);

	Room * a = new Room(14, 1, 3, 3);
	Room * b = new Room(10, 6, 3, 3);
	rooms.push_back(a);
	rooms.push_back(b);
	root.createHall(a, b);

	Room * c = new Room(1, 14, 3, 3);
	Room * d = new Room(6, 10, 3, 3);
	rooms.push_back(c);
	rooms.push_back(d);
	root.createHall(c, d);

	Room * e = new Room(14, 14, 3, 3);
	Room * f = new Room(10, 10, 3, 3);
	rooms.push_back(e);
	rooms.push_back(f);
	root.createHall(e, f);

	Room * g = new Room(18, 8, 3, 3);
	Room * h = new Room(23, 8, 3, 3);
	Room * i = new Room(28, 8, 3, 3);
	Room * j = new Room(23, 4, 3, 3);
	Room * k = new Room(23, 13, 3, 3);
	rooms.push_back(g);
	rooms.push_back(h);
	rooms.push_back(i);
	rooms.push_back(j);
	rooms.push_back(k);
	root.createHall(g, h);
	root.createHall(h, i);
	root.createHall(j, h);
	root.createHall(h, k);

	Room * lv = new Room(33, 10, 3, 5);
	Room * m = new Room(38, 8, 3, 3);
	Room * n = new Room(43, 5, 3, 3);
	Room * o = new Room(36, 4, 3, 3);
	Room * p = new Room(40, 13, 3, 3);
	rooms.push_back(lv);
	rooms.push_back(m);
	rooms.push_back(n);
	rooms.push_back(o);
	rooms.push_back(p);
	root.createHall(lv, m);
	root.createHall(m, n);
	root.createHall(o, m);
	root.createHall(p, m);

	for (Room* l : rooms){
		for (int x = l->getX1(); x < l->getX2(); x++){
			for (int y = l->getY1(); y < l->getY2(); y++){
				tiles[x + y*Mwidth] = new Floor(x * 15, y * 15);
			}
		}
	}
	*/
	for (Leaf* l : leaves){
		if (l->getRoom() != NULL){
			int red = rand() % 255;
			int green = rand() % 255;
			int blue = rand() % 255;
			Room* room = l->getRoom();
			rooms.push_back(room);
			for (int x = room->getX1(); x < room->getX2(); x++){
				for (int y = room->getY1(); y < room->getY2(); y++){
					tiles[x + y*Mwidth] = new Floor(x * 15, y * 15);
					((Floor*)tiles[x + y*Mwidth])->r = red;
					((Floor*)tiles[x + y*Mwidth])->g = green;
					((Floor*)tiles[x + y*Mwidth])->b = blue;
					((Floor*)tiles[x + y*Mwidth])->a = 255;
				}
			}
		}
		
		if (l->getHall().size() > 0){
			for (Hall* h : l->getHall()){
				halls.push_back(h);
				int red = rand() % 255;
				int green = rand() % 255;
				int blue = rand() % 255;
				for (int x = h->getX1(); x < h->getX2(); x++){
					for (int y = h->getY1(); y < h->getY2(); y++){
						tiles[x + y * Mwidth] = new Floor(x * 15, y * 15);
						((Floor*)tiles[x + y*Mwidth])->r = red;
						((Floor*)tiles[x + y*Mwidth])->g = green;
						((Floor*)tiles[x + y*Mwidth])->b = blue;

					}
				}
			}
		}
	}
}
