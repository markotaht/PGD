#include "map.h"

Map::Map(int width, int height):
Mwidth(width),
Mheight(height)
{
	for (int y = 0; y < height; y++){
		for (int x = 0; x < width; x++){
			tiles.push_back(new Wall(TILE_SIZE * x, TILE_SIZE*y));
			if (rand() % 100 < chasetostartAlive){
				cells.push_back(true); 
			}
			else{
				cells.push_back(false);
			}
		}
	}
}

void Map::render(SDL_Renderer* renderer){
	for (std::vector<Tile*>::iterator it = tiles.begin(); it != tiles.end(); it++){
		(*it)->render(renderer);
	}
}

void Map::generateMap(){
	for (int i = 0; i < 20; i++){
		cells = doGenerationStep(cells);
	}
	for (int i = 0; i < cells.size(); i++){
		if(cells[i]) tiles[i] = new Floor(tiles[i]->getX(), tiles[i]->getY());
	}
}

std::vector<bool> Map::doGenerationStep(std::vector<bool> cells){
	std::vector<bool> newcells(cells);
	for (int x = 0; x < Mwidth; x++){
		for (int y = 0; y < Mheight; y++){
			int neigbours = countNeigbours(cells, x, y);
			if (cells[x + y*Mwidth]){
				if (neigbours < deathlimit){
					newcells[x + y*Mwidth] = false;
				}
				else{
					newcells[x + y*Mwidth] = true;
				}
			}
			else{
				if (neigbours > birthlimit){ 
					newcells[x + y*Mwidth] = true; 
				}
				else{ 
					newcells[x + y*Mwidth] = false; 
				}
			}
		}
	}
	return newcells;
}

int Map::countNeigbours(std::vector<bool> cells, int x, int y){
	int count = 0;
	for (int i = -1; i < 2; i++){
		for (int j = -1; j < 2; j++){
			int n_x = x + i;
			int n_y = y + j;
			if (i == 0 && j == 0){}
			else if (n_x < 0 || n_y < 0 || n_x >= Mwidth || n_y >= Mheight){ 
				count++; 
			}
			else if (cells[n_x + n_y*Mwidth]){
				count++;
			}
		}
	}
	return count;
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
				if (l->getWidth() > MAX_ROOM_SIZE || l->getHeight() > MAX_ROOM_SIZE || rand() % 10 > 5){
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
					tiles[x + y*Mwidth] = new Floor(TILE_SIZE * 15, TILE_SIZE * 15);
					((Floor*)tiles[x + y*Mwidth])->r = red;
					((Floor*)tiles[x + y*Mwidth])->g = green;
					((Floor*)tiles[x + y*Mwidth])->b = blue;
					((Floor*)tiles[x + y*Mwidth])->a = 255;
				}
			}
		}
	//}
		//	createHalls();
		if (l->getHall().size() > 0){
			for (Hall* h : l->getHall()){
				//for (Hall* h: halls){
				halls.push_back(h);
			/*	int red = rand() % 255;
				int green = rand() % 255;
				int blue = rand() % 255;
				for (int x = h->getX1(); x <= h->getX2(); x++){
					for (int y = h->getY1(); y <= h->getY2(); y++){
						tiles[x + y * Mwidth] = new Floor(x * 15, y * 15);
						((Floor*)tiles[x + y*Mwidth])->r = red;
						((Floor*)tiles[x + y*Mwidth])->g = green;
						((Floor*)tiles[x + y*Mwidth])->b = blue;

					}
				}*/
			}
		}
	}


	for (std::vector<Hall*>::iterator it = halls.begin(); it != halls.end();){
		for (std::vector<Hall*>::iterator it2 = halls.begin(); it2 != halls.end();){
			bool erase = false;
			if (it != it2){
				if ((*it)->getHeight() != 1 && (*it2)->getHeight() != 1){
					if ((*it)->getX1() + 1 == (*it2)->getX1() || (*it)->getX1() - 1 == (*it2)->getX1()){
						it2 = halls.erase(it2);
						erase = true;
					}
				}
				if ((*it)->getWidth() != 1 || (*it2)->getWidth() != 1){
					if ((*it)->getY1() + 1 == (*it2)->getY1() || (*it)->getY1() - 1 == (*it2)->getY1()){
						it2 = halls.erase(it2);
						erase = true;
					}
					
				}
			}
			if(!erase){
				++it2;
			}
		}
		++it;
	}


	for (Hall* h : halls){
		int red = rand() % 255;
		int green = rand() % 255;
		int blue = rand() % 255;
		for (int x = h->getX1(); x <= h->getX2(); x++){
			for (int y = h->getY1(); y <= h->getY2(); y++){
				tiles[x + y * Mwidth] = new Floor(TILE_SIZE * 15, TILE_SIZE * 15);
				((Floor*)tiles[x + y*Mwidth])->r = red;
				((Floor*)tiles[x + y*Mwidth])->g = green;
				((Floor*)tiles[x + y*Mwidth])->b = blue;

			}
		}
	}
}


void Map::createHalls(){
	Leaf* root = new Leaf(0,0,0,0);
	for (Room* r : rooms){
		Room * up = NULL;
		Room * down = NULL;
		Room * left = NULL;
		Room * right = NULL;
		int minup = INT_MAX, mindown = INT_MAX, minleft = INT_MAX, minright = INT_MAX;
		for (Room* l : rooms){
			if (r != l){
				if (!(r->checkConnection(l))){
					if (r->getX1() < l->getX1()){
						if (l->getX1() - r->getX1() < minright){
							minright = l->getX1() - r->getX1();
							right = l;
						}
					}
					
					if (l->getX1() < r->getX1()){
						if (r->getX1() - l->getX1() < minleft){
							minleft = r->getX1() - l->getX1();
							left = l;
						}
					}

					if (r->getY1() < l->getY1()){
						if (l->getY1() - r->getY1() < mindown){
							mindown = l->getY1() - r->getY1();
							down = l;
						}
					}

					if (r->getY1() > l->getY1()){
						if (r->getY1() - l->getY1() < minup){
							minup = r->getY1() - l->getY1();
							up = l;
						}
					}
				}
			}
		}
		if (rand() % 10 > 5 && (up != NULL || down != NULL)){
			if (rand() % 10 > 5 && up != NULL){
				root->createHall(r, up);
			}
			else{
				if (down != NULL)
				root->createHall(r, down);
			}
		}
		else{
			if (rand() % 10 > 5 && left != NULL){
				root->createHall(r, left);
			}
			else{
				if (right != NULL)
				root->createHall(r, right);
			}
		}
	}
	for (Hall* h : root->getHall()){
		halls.push_back(h);
	}
}